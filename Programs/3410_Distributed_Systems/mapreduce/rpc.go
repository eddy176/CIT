package mapreduce

import (
	"log"
	"path/filepath"
)

// Register is cool
func (m *Master) Register(address string, resp *Nothing) error {
	log.Printf("Register was called for new worker %s\n", address)
	m.Mut.Lock()
	m.Workers = append(m.Workers, &Worker{Address: address, Available: true})
	m.Mut.Unlock()
	m.assignTasks()
	return nil
}

func (m *Master) handleMap(worker *Worker, task MapTask) {
	m.Mut.Lock()
	defer m.Mut.Unlock()
	address := worker.Address
	// Create URL's for completed map task in reduce tasks
	for _, reduce := range m.ReduceTasks {
		outFile := mapOutputFile(task.N, reduce.N)
		url := makeURL(address, outFile)
		reduce.SourceHosts = append(reduce.SourceHosts, url)
	}

	worker.Available = true
	m.MapCompleted++
	log.Printf("Completed map tasks is %d\n", m.MapCompleted)
	m.assignTasks()
}

func (m *Master) handleReduce(worker *Worker, task *ReduceTask) {
	m.Mut.Lock()
	defer m.Mut.Unlock()

	// Store reduce URLs. Gather when complete
	url := makeURL(worker.Address, reduceOutputFile(task.N))
	m.OutputURLs = append(m.OutputURLs, url)

	worker.Available = true
	m.ReduceCompleted++
	m.assignTasks()
}

func (m *Master) assignTasks() {
	go func() {
		m.Mut.Lock()
		defer m.Mut.Unlock()

		// All reduce tasks complete. Shutdown!
		if m.ReduceCompleted >= m.R {
			tempFile := filepath.Join(m.Files, "master_temp.sqlite3")
			finalFile := filepath.Join(m.Files, "master_output.sqlite3")
			mergeDatabases(m.OutputURLs, finalFile, tempFile)

			for _, worker := range m.Workers {
				log.Printf("Shutting down worker %v\n", worker.Address)
				err := call(worker.Address, "Worker.Shutdown", struct{}{}, &struct{}{})
				Fail("assignTasks: MapTask", err)
			}
			log.Println("Merge reduce output here")
			// log.Printf("Master's state %+v\n", m)
			m.Kill <- true
		}
		// Assign works map and reduce task

		for _, worker := range m.Workers {
			if !worker.Available {
				continue
			}
			if len(m.MapTasks) > 0 {
				mapTask := m.MapTasks[0]
				m.MapTasks = m.MapTasks[1:]
				worker.Available = false
				log.Println(mapTask)

				go func(w *Worker, task MapTask) {
					
					address := w.Address
					log.Printf("worker %s assigned map task %d\n", address, task.N)
					err := call(address, "Worker.RunMap", task, &struct{}{})
					Fail("assignTasks: MapTask", err)
					m.handleMap(w, task)
				}(worker, mapTask)
				continue
			} else if m.MapCompleted >= m.M && len(m.ReduceTasks) > 0 {
				reduceTask := m.ReduceTasks[0]
				m.ReduceTasks = m.ReduceTasks[1:]
				worker.Available = false

				go func(w *Worker, task *ReduceTask) {
					address := w.Address
					log.Printf("worker %s assigned reduce task %d\n", address, task.N)
					err := call(address, "Worker.RunReduce", task, &struct{}{})
					Fail("assignTasks: ReduceTask", err)
					m.handleReduce(w, task)
				}(worker, reduceTask)
				continue
			}
		}
	}()
}

// Shutdown is cool
func (w *Worker) Shutdown(n Nothing, nun *Nothing) error {
	log.Println("Shutdown called")
	w.Kill <- true
	return nil
}

// RunMap is cool
func (w *Worker) RunMap(task MapTask, n *Nothing) error {
	log.Printf("Received map task %d\n", task.N)
	task.Process(w.Dir, w.Client)
	log.Printf("Map task %d completed", task.N)
	return nil
}

// RunReduce is cool
func (w *Worker) RunReduce(task ReduceTask, n *Nothing) error {
	log.Printf("Received reduce task %d\n", task.N)
	task.Process(w.Dir, w.Client)
	log.Printf("Reduce task %d completed", task.N)
	return nil
}
