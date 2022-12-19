#!/usr/bin/env bash
cmake -S . -B build && make --directory build && pushd build && \
echo "--------------------------------------"; \
./spa;\
echo "--------------------------------------"; \
popd;