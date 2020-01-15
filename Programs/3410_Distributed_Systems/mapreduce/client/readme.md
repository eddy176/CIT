## Installation

Repository must be installed in path `$GOPATH/src/mapreduce`

## Running

In directory `client/` run command `go build`

#### Splitting

```
./client -split -dir ./tmp ./austen.sqlite3
```

`-split` is a flag. The value with `-dir` will be the directory that
the output files will be stored. The last arugument has to be the source
file to be split. I set up splitting to be seperate from running the master.

#### Master

```
./client -m 12 -r 4 -dir ./tmp -master
```

Only the master needs to define `-m` and `-r`, `-dir` to be `./tmp` in the project, and `-master`.

#### Worker

```
./client -ip 144.38.173.201:3410:3410 -port 3411
```

The worker only needs to give `-ip`, which is the location of the master, and
`-port` which is the port this worker will listen on. Nothing else is needed.
