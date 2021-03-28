# anthill-game-engine

Now, its jast a some kind of trash with plan. Look at the future...

# Goals

- #### Logging
:white_check_mark: Make logger strategy interface
:white_check_mark: Implement logger strategy interface logic
:white_check_mark: Make scoped logger interface
:white_check_mark: Implement scoped logger interface logic
:black_square_button: Think about async write to buffer [wip]

---

- ### Config manager

:black_square_button: Make Interface for configuration loading

- From file
- From stream

:black_square_button: Add interface implementation as json/xml/tson loader

---

- ### Zip undixing utils

:black_square_button: Add zip undixing interface
:black_square_button: Make logic

---

- ### File manager

:black_square_button: Add interface for loading files
:black_square_button: Inplement interface

- As stream
- As simple file discriptor

:black_square_button: Make Zip utils as part of manager

---

- ### Engine core

:black_square_button: Make core :)
<details>
    <summary>Core structure</summary>

Methids:

- Initialize
- Load modules (use next point)
- Cycle

---

Contain:

- Module map (standart module will set like interfase, other like {string dll name: void\*) )
- Config manager

</details>

---

- ### Module loading
  | Make wrapper for winapi hot(runtime) dll loading |

:black_square_button: Define shared module interfase
:black_square_button: Think about key kripted libs (loader will uncript libs and load in memory, is it real???)
:black_square_button: Make Logging/File manager as modules

<details>
    <summary>Module logic</summary>

- All midule load as dll in runtime
- All module must contain interface in .hpp file (for cast and usage in code)
- All module contain function:

  1. Load (take pointer to core; build module and return it like void\*)
  2. Unload (take void\* to mudule and distruct it)

- Some module can contain functions:
  1. Tick with time after last tick

</details>

---

- ### Window manager (as module)

:black_square_button: Make window class interface
:black_square_button: Implenment interface with SDL2

---

- ### Gui system (as module)

:black_square_button: Understand how imgui framework independent
:black_square_button: Steal some gui code)) and make widget system

- Add layout widgets
- Make font loading with sdl2 ttf lib

:black_square_button: Understand how process two window

---

- ### Core part 2

:black_square_button: Add to core opening window with views:

- Make project
- Open project

:black_square_button: Make project file

<details>
    <summary>Project file format</summary>
    Here will be project files format :)
</details>

---

- ### Resource manager

:black_square_button: Make interface for objects manager
:black_square_button: Make logic (use File manager with zip logic for loading data)

---

- ### Render system

:black_square_button: Load object with resource manager and draw it
      | It will not so simple, I know that we need some game object abstruction, but... its for test and some expiriance, idk how it realize |

:black_square_button:

---

- ### Core part 3

:black_square_button: Add button wich open window and use Render system for test drawing objects

---

- ### Make some object ubstruction. I think it will be different game objects manager with void\* to castom data and observer like script logic, need thinks
<details>
    <summary>Thoughts</summary>
Make template function, which will take objects from map and cast in to T type. Idk how it make better, need some ideas
</details>

---

- ### Physics system

:black_square_button: Chose and add Physics engine like module

---

- ### Script system

:black_square_button: Make single storage, which will contain map with pointer to scripts
:black_square_button: In develop mode it will be different dll, which load in runtime and observe some game object; In release build its one dll for language, from which we load logic
      | And this chose cool, because: we can use C++/C/Rust/Go/etc with C abi in one time!!! We even can make module which load python intrpreter and then we make script which call python script from this module. Yes, im crazy :) |

---

- ### Make build system

:black_square_button: System will generate all artefacts

---

- ### Some other trash :)

:black_square_button: IDK, ist will be in next time

---

- I think about node generated libs. If I find way how to make it, we will can change render system or something other module for engine and release artefact as a simple grapth.

- If I make something usefull, you can take it for you code

- If you have any idea, I want think with you - Evgenuy1605@yandex.ru
