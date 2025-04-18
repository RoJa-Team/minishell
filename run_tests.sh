#!/bin/bash

# === Config ===
MINISHELL_PATH=./minishell
TEST_FILE=./test_commands_extreme.txt
OUT_BASH=output_bash.txt
OUT_MINISHELL=output_minishell.txt
OUT_MINISHELL_NOPROMPT=output_minishell_no_prompt.txt
OUT_MINISHELL_CLEAN=output_minishell_no_prompt_no_heredoc.txt

# === Safety checks ===
if [ ! -x "$MINISHELL_PATH" ]; then
  echo "❌ Error: minishell binary not found at $MINISHELL_PATH"
  exit 1
fi

if [ ! -f "$TEST_FILE" ]; then
  echo "❌ Error: test_commands.txt not found!"
  exit 1
fi

# === Output setup ===
> "$OUT_BASH"
> "$OUT_MINISHELL"
> "$OUT_MINISHELL_NOPROMPT"
> "$OUT_MINISHELL_CLEAN"

# === Run Bash ===
echo "▶ Running in Bash..."
bash < "$TEST_FILE" > "$OUT_BASH" 2>&1

# === Run Minishell ===
echo "▶ Running in Minishell..."
$MINISHELL_PATH < "$TEST_FILE" > "$OUT_MINISHELL" 2>&1

# === Strip minishell prompts ===
echo "▶ Removing \$minishell> prompts..."
grep -v '^\$minishell>' "$OUT_MINISHELL" > "$OUT_MINISHELL_NOPROMPT"

# === Remove heredoc prompts too ===
echo "▶ Removing heredoc> prompts..."
grep -v '^heredoc>' "$OUT_MINISHELL_NOPROMPT" > "$OUT_MINISHELL_CLEAN"

# === Report ===
echo ""
echo "✅ Tests completed!"
echo "📝 Bash output:                            $OUT_BASH"
echo "📝 Minishell full output:                  $OUT_MINISHELL"
echo "📝 Minishell no prompt:                    $OUT_MINISHELL_NOPROMPT"
echo "📝 Minishell no prompt & no heredoc:       $OUT_MINISHELL_CLEAN"
echo ""
echo "🔍 To compare clean outputs, run:"
echo "diff -u $OUT_BASH $OUT_MINISHELL_CLEAN | less"
