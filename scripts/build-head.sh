#!/usr/bin/env bash
# Builds the engine at HEAD and copies it to build/khez-head.

# stop on errors, on undefined vars, and on failed pipes
set -euo pipefail

# repo root, so the script works from any cwd
REPO_ROOT="$(git rev-parse --show-toplevel)"
# unique temp dir for the worktree (allows parallel runs)
WORKTREE_DIR="$(mktemp -d -t khez-head-XXXXXX)"
OUT_BIN="${REPO_ROOT}/build/khez-head"

# always remove the worktree on exit (success, error, Ctrl+C)
cleanup() {
    git -C "${REPO_ROOT}" worktree remove --force "${WORKTREE_DIR}" >/dev/null 2>&1 || true
    rm -rf "${WORKTREE_DIR}"
}
trap cleanup EXIT

# second checkout of the repo at HEAD, detached (no branch attached)
echo ">> creating worktree at ${WORKTREE_DIR} (HEAD)"
git -C "${REPO_ROOT}" worktree add --detach "${WORKTREE_DIR}" HEAD

# -S source dir, -B build dir, Release picks the optimized flags
echo ">> configuring"
cmake -S "${WORKTREE_DIR}" -B "${WORKTREE_DIR}/build" -DCMAKE_BUILD_TYPE=Release

# -j parallel build, only the khez target (skip tests)
echo ">> building"
cmake --build "${WORKTREE_DIR}/build" -j --target khez

# copy the binary out before cleanup wipes the worktree
mkdir -p "${REPO_ROOT}/build"
cp "${WORKTREE_DIR}/build/khez" "${OUT_BIN}"

echo ">> done: ${OUT_BIN}"
