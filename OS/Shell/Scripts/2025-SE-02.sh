#!/bin/bash

if [[ -z "$SVC_DIR" ]]; then
  echo "env file doesnt exist"
  exit 1
fi 

if [[ "${#}" -lt 1 ]]; then
    exit 1
fi

if [[ ! -d "${SVC_DIR}" ]]; then
    echo "SVC_DIR is not a valid directory"
    exit 1
fi

cmd="$1"

if [[ "$cmd" == "start" ]]; then
    srv="$2"

    if [[ -z "$svc" ]]; then
        echo "Missing service name"
        exit 1
    fi

    find "$SVC_DIR" -type f | while read -r file; do
        name=$(grep "^name:" "$file" | cut -d ':' -f2- | xargs)
        if [[ "$name" != "$svc" ]]; then
            continue
        fi

        pidfile=$(grep "^pidfile:" "$file" | cut -d ':' -f2- | xargs)
        outfile=$(grep "^outfile:" "$file" | cut -d ':' -f2- | xargs)
        comm=$(grep "^comm:" "$file" | cut -d ':' -f2- | xargs)

        if [[ -f "$pidfile" ]] && kill -0 "$(cat "$pidfile")" 2>/dev/null; then
            exit 0
        fi

        bash -c "$comm" >> "$outfile" 2>&1 &   # eval "$comm >> \"$outfile\" 2>&1 &"
        echo $! > "$pidfile"
        exit 0
    done
elif [[ "$command" == "stop" ]]; then
    srv="$2"

    if [[ -z "$svc" ]]; then
        echo "Missing service name"
        exit 1
    fi

    find "$SVC_DIR" -type f | while read -r file; do
        name=$(grep "^name:" "$file" | cut -d ':' -f2- | xargs)
        if [[ "$name" != "$svc" ]]; then
            continue
        fi

        pidfile=$(grep "^pidfile:" "$file" | cut -d ':' -f2- | xargs)

        if [[ -f "$pidfile" ]] && kill -0 "$(cat "$pidfile")" 2>/dev/null; then
            kill "$(cat "$pidfile")"
        fi

        exit 0
    done
elif [[ "$command" == "running" ]]; then
    result=""

    find "$SVC_DIR" -type f | while read -r file; do
        name=$(grep "^name:" "$file" | cut -d ':' -f2- | xargs)
        pidfile=$(grep "^pidfile:" "$file" | cut -d ':' -f2- | xargs)

        if [[ -f "$pidfile" ]] && kill -0 "$(cat "$pidfile")" 2>/dev/null; then
            echo "$name"
        fi
    done | sort
elif [[ "$command" == "cleanup" ]]; then
    find "$SVC_DIR" -type f | while read -r file; do
        pidfile=$(grep "^pidfile:" "$file" | cut -d ':' -f2- | xargs)

        if [[ -f "$pidfile" ]] && ! kill -0 "$(cat "$pidfile")" 2>/dev/null; then
            rm -f "$pidfile"
        fi
    done

else
    echo "Unknown command: $command"
    exit 1
fi
