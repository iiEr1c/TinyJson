# perf
```shell
# -g = --call-graph fp
# fp, dwarf, lbr
perf record -F 99 --call-graph dwarf ./app

perf script > out.perf

git clone https://github.com/brendangregg/FlameGraph.git

./stackcollapse-perf.pl out.perf > out.folded
./flamegraph.pl out.folded > test.svg
```