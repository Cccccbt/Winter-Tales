## Repository layout

- `Winter Tales/` — primary C++ source for the 2D action prototype, including a Visual Studio solution (`Winter Tales.sln`).
- `C++ Winter Tales/` and `cpp Winter Tales/` — earlier code experiments kept for reference.
- `index.html` & `mystyle.css` — single-page marketing site for the "Winter Tales" hackathon theme.
- `resources/` (inside `Winter Tales/`) — sprites and audio used by the C++ build.

## C++ game overview

The game uses the EasyX/Win32 graphics stack (`<graphics.h>`) to render a side-view action scene with a player character and a magic bear boss. The main loop boots resources, polls Windows messages, updates state machines for the player and enemies, and draws the scene at a fixed 60 FPS.

### Prerequisites

- Windows with Visual Studio 2022 (or newer) and the Desktop development with C++ workload.
- EasyX (or a compatible `<graphics.h>` implementation) installed and discoverable by the compiler and linker.
- Ensure the working directory when running the executable contains the `resources/` folder referenced in `ResourceManager`.

### Build and run

1. Open `Winter Tales.sln` in Visual Studio.
2. Confirm your VC++ directories include the EasyX headers and libraries.
3. Build the `Winter Tales` project (Debug or Release).
4. Run from Visual Studio or launch the generated executable with the repository root as the working directory so resource paths resolve.

### Controls

Input is handled through Windows key messages (`WM_KEYDOWN`/`WM_KEYUP`):

- Move: `A` / `D` (or `←` / `→`).
- Jump: `W` (or `↑`).
- Roll/Dodge: `S` (or `↓`).
- Attacks: `J` and `K` trigger different attack states.
- Bullet time: `Space` slows time using `BulletTimeManager`.
- Debug overlay: press `Q` to toggle collision debug rendering.

## Static site

The landing page lives in `index.html` with styles in `mystyle.css`. Open `index.html` directly in a browser or host the folder with any static server to preview the design.

## Contributing

- Keep Visual Studio project files and resource paths in sync with any new assets you add.
- Align new controls or behaviors with the existing state machine and input handling patterns in `player.cpp` and related state node files.
- For front-end changes, mirror the existing structure and naming in `index.html`/`mystyle.css` to maintain consistency.

