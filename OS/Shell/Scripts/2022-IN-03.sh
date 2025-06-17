#!/bin/bash

# works like the old implementation but internally calls the new implementation correctly.
# bashjava [options] -jar filename [args]
# options: optional Java options (each starts with -)
# filename: JAR file to execute (always used with -jar)
# args: optional arguments for the main() method
# old implementation:
# - Everything after the JAR filename are arguments for main()
# - The JAR filename comes somewhere after the -jar option
# - Java options can appear both before AND after the -jar option
# - The -Dproperty=value option only works if it appears AFTER the -jar option

# Non-standard way:
# java -jar ./app.jar -Dqux=foo default
# java -Dqux=foo -jar ./app.jar -hoge fuga
# java -jar -Dqux=foo app.jar

# Should become standard:
# java -Dqux=foo -jar ./app.jar default
# java -Dqux=foo -jar ./app.jar -hoge fuga 
# java -Dqux=foo -jar app.jar

# Parse the non-standard command line arguments
# Separate Java options, JAR filename, and program arguments
# Reorders them to match standard Java syntax
# Calls the standard java command with the corrected arguments

# The script needs to handle the parsing logic to extract:
# Java options (including -D properties) from anywhere in the command line
# The JAR filename (first argument after -jar that doesn't start with -)
# Everything after the JAR filename as program arguments

java_options=()
jar_file=""  # for the file name
program_args=()  # for the main()

found_jar=false        # found -jat option
found_jar_file=false   # found name

i=1
while [[ "$i" -le "$#" ]]; do
    arg="${!i}"              # Get the i-th argument using indirect expansion

    if [[ "$found_jar" == false ]]; then
        if [[ "$arg" == "-jar" ]]; then
            found_jar=true
        else
            java_options+=("$arg")
        fi
    elif [[ "$found_jar_file" == false ]]; then
        if [[ "$arg" == -* ]]; then
            java_options+=("$arg")
        else
            jar_file="$arg"
            found_jar_file=true
        fi
    else
        program_args+=("$arg")
    fi
    
    i=(("$i"+ 1))    
done

if [[ "$found_jar" == false ]] || [[ "$found_jar_file" == false ]]; then
    echo "Error: -jar option or JAR file not found"
    exit 1
fi

java_cmd="java"

for option in "${java_options[@]}"; do
    java_cmd="$java_cmd $option"
done

java_cmd="$java_cmd -jar $jar_file"

for arg in "${program_args[@]}"; do
    java_cmd="$java_cmd $arg"
done

exec $java_cmd

# Common Patterns in These Problems:
# State Machine Parsing - Like the Java example, you need to track what phase of parsing you're in
# Categorizing Arguments - Separating options, files, commands, and parameters
# Order Dependencies - Some arguments must come before others
# Backward Compatibility - Supporting old syntax while using new tools
# Argument Validation - Ensuring required elements are present

# Key Techniques Used:
# Multi-phase parsing (like the 3 phases in the Java example)
# Array manipulation for grouping similar arguments
# Pattern matching to identify argument types
# State flags to track parsing progress
# Command reconstruction to build the final command