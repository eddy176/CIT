## Installation

Repository must be installed in path `$GOPATH/src/mapreduce`

## Running

run command `go build`


#### Paxos

```
run these on 3 different terminals
./paxos 3410 3411 3412
./paxos 3411 3410 3412
./paxos 3412 3410 3411
```

Only the master needs to define `-m` and `-r`, they will also default to 9 and 3.
I have been setting `-dir` to be `./tmp` in the project. If `-dir` is not defined
then it will default to a temporay directory that will be removed when the master
shuts down. `-master` is just a flag.