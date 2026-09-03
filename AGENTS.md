# Agent guidance

## xemu overlay repo

`xemu/` is a separate git repo nested in this QEMU tree. Put new project-owned
files under `xemu/` so upstream QEMU upgrades stay easier.

- Good: `xemu/.cursor/plans/`, `xemu/.cursor/rules/`, other new docs/scripts/config
  under `xemu/`
- Bad: adding those new files at the QEMU repo root or under upstream paths when
  they belong to the xemu overlay

Edit upstream QEMU sources only when the task requires it. Prefer overlaying or
documenting under `xemu/` when that is enough.

Root `meson.build` pulls the overlay with `subdir('xemu')` and adds `-iquote`
for `xemu/include`. Overlay `subdir()` entries live in `xemu/meson.build`.

## Mirror QEMU layout under xemu/

Keep `xemu/` paths parallel to the QEMU tree so related code is easy to find.
When adding a new xemu-owned file that corresponds to a QEMU area, place it at
the same relative path under `xemu/`.

| QEMU path | xemu path |
| --- | --- |
| `tests/<area>/` | `xemu/tests/<area>/` |
| `include/<area>/` | `xemu/include/<area>/` |
| `hw/<area>/` | `xemu/hw/<area>/` |
| `system/` | `xemu/system/` |
| `docs/<area>/` | `xemu/docs/<area>/` |
| `scripts/<area>/` | `xemu/scripts/<area>/` |
| `tests/meson.build` (xemu-only subdirs) | `xemu/tests/meson.build` |

Upstream QEMU files may still need small hooks (includes, `subdir()`, option
forwarding, or glue compiled into a QEMU module). Keep those hooks minimal;
put the bulk of new code under `xemu/`.

Root `meson.build` pulls overlay tests with `subdir('xemu/tests')` next to
`subdir('tests')`. List overlay test subdirs in `xemu/tests/meson.build`.

xemu-only areas with no QEMU counterpart stay as dedicated top-level dirs:

- `xemu/.cursor/plans/` - Cursor plan files
- `xemu/.cursor/rules/` - Cursor rule files
- `xemu/lic/` - project license / machine-id code
- build/configure/release scripts at `xemu/` root

## Plans

Always save Cursor plan files (`*.plan.md`) under `xemu/.cursor/plans/`:

- Good: `xemu/.cursor/plans/<name>.plan.md`
- Bad: any path under the user home Cursor folder (e.g. `~/.cursor/plans/`,
  `C:/Users/<user>/.cursor/plans/`), `<workspace>/.cursor/plans/`, or any other
  path outside `xemu/.cursor/plans/`

Create `xemu/.cursor/plans/` if it is missing. Prefer `*.plan.md` names. Never
create, move, or save plan files outside `xemu/.cursor/plans/`. If a tool or UI
defaults to the user-level plans directory, write the plan into
`xemu/.cursor/plans/` instead.

## Rules

Always create or edit Cursor rule files under `xemu/.cursor/rules/`:

- Good: `xemu/.cursor/rules/<name>.mdc`
- Bad: `.cursor/rules/`, `~/.cursor/rules/`, or any other path outside
  `xemu/.cursor/rules/`

Use `.mdc` with YAML frontmatter (`description`, `globs`, `alwaysApply` as
needed). Do not write new rules under `.cursor/rules/` even if `/create-rule`
or the UI defaults there.

Existing always-apply rules in `xemu/.cursor/rules/`:

- `xemu-msys2-mingw64-build.mdc` - Windows MSYS2 MinGW64 builds
- `minimal-and-safe-editing.mdc` (`mase`) - minimal diffs and encoding
- `no-edk2-edits.mdc` - do not touch `roms/edk2/`
- `no-vscode-edits.mdc` - do not touch `.vscode/`

## Windows shells (required on win32)

This tree is built and smoke-tested under **MSYS2 MinGW64**, not WSL and not
Git Bash by default. Details live in
`xemu/.cursor/rules/xemu-msys2-mingw64-build.mdc`.

This workspace is `C:\work\xemu\xemu`. Ninja trees are `build/debug` and
`build/release`. Do not treat `build/` or `build-debug` as the ninja directory.

On Windows, never invoke bare `bash`, `C:\Windows\System32\bash.exe`, or
WindowsApps bash: those are WSL stubs and will not see MinGW tools or DLLs.

Use:

```
C:/CI-Tools/msys64/usr/bin/bash.exe --login
```

with `MSYS=winsymlinks:native`, `MSYSTEM=MINGW64`, `CHERE_INVOKING=1` (and
`DESTDIR=../../xemu-dist/mingw64` for builds). Run repo scripts the same way,
for example:

```powershell
$env:MSYS='winsymlinks:native'; $env:MSYSTEM='MINGW64'; $env:CHERE_INVOKING='1'
C:/CI-Tools/msys64/usr/bin/bash.exe --login -c "cd /c/work/xemu/xemu && BUILD=build/debug ./xemu/tests/machine-memory-bank/memory-bank-smoke.sh"
```

Prefer an existing `bash Build XEMU Debug` / Release terminal from
`.vscode/settings.json` when one is already open, then `cd` to `build/debug`
or `build/release` before `ninja`.

## Commit title style (required)

This section is mandatory for every commit in this repo. Do not skip it.
User-level commit habits do not override it.

### Before every commit

1. Run `git log -15 --format='%s'` and match the surrounding title pattern.
2. Draft the title as `area: imperative summary`.
3. Reject the title if it has no `area:` prefix, unless step 1 shows nearby
   commits for the same kind of change also omit it (rare).
4. Only then run `git commit`.

### Title form

- Required shape: `area: imperative summary`
- `area` is the subsystem, path prefix, or file stem that owns the change.
  Examples: `monitor:`, `docs:`, `gitlab:`, `hw/usb/hcd-xhci:`, `target/arm:`,
  `treewide:`, `virtio-gpu:`, `xemu-launch:`, `AGENTS.md:`, `.clangd:`,
  `.vscode:`.
- After the colon, use an imperative verb: `fix`, `add`, `remove`, `update`,
  `include` (sentence case is also common: `Fix`, `Add`, `Remove`).
- Keep the title short and concrete.
- Do not use Conventional Commits (`feat:`, `chore:`) unless nearby history
  already does.
- Do not use a bare title like `Add X` when an `area:` exists. Root docs and
  tooling still have an area (`AGENTS.md:`, `.clangd:`, `.vscode:`).

### Good

- `monitor: fix -Warray-bounds on MinGW release builds`
- `docs: fix sphinx build failure`
- `hw/sd/sdcard: Fix error case for CMD18`
- `virtio-gpu: add test= GModule backend via xemu overlay`
- `AGENTS.md: add commit title style guidance`
- `.clangd: add Windows/MSYS2 clangd and clang-format config`
- `.vscode: add workspace settings and extension recommendations`

### Bad

- `Add commit title style guidance to AGENTS.md.` (missing `AGENTS.md:`)
- `Add clangd config and VS Code workspace settings for Windows/MSYS2.`
  (should be `.clangd:` / `.vscode:` or split commits)
- `Fixed stuff`
- `feat: improve clangd`
- `Update files`
