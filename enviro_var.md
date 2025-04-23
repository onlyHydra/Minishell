Requirements Summary

Detect and expand $VAR_NAME (alphanumeric + underscore)
Optionally handle ${VAR} syntax
Support special variable $? (exit status)
Handle single quotes (no expansion)
Handle double quotes (allow expansion)
Handle edge cases like empty variables

Overall Plan

Create functions to detect environment variables
Create functions to expand environment variables
Modify the token processing logic to handle quotes correctly
Update the tokenizer to distinguish between different quote types
Integrate with your existing code in string_tokenize.c

Let's break this down into steps:
Step 1: Create Environment Variable Detection Functions
First, we need functions to:

Identify when we encounter a $ followed by a valid variable name
Check if it's inside single quotes (where no expansion happens)
Extract the variable name
Look up the value in the environment

Step 2: Create Variable Expansion Functions
These will:

Handle the special $? case
Handle regular environment variables
Support empty variables correctly
Optionally handle ${VAR} syntax

Step 3: Modify Token Processing Logic
We'll need to:

Track quote states (single, double, or none)
Only perform expansion when appropriate (outside single quotes)
Keep track of the last exit status
