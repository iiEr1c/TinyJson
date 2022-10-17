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

# reference
+ [从零开始的 JSON 库教程](https://github.com/miloyip/json-tutorial)