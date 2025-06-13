#!/bin/bash

if [[ "${#}" -ne 1 ]]; then
    echo "Needs to be 1 arg"
    exit 1
fi

if [[ ! -d "${1}" ]]; then
    echo "Needs to be dir"
    exit 1
fi

