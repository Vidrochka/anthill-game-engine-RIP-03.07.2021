# anthill-game-engine

Now, its jast a some kind of trash with plan. Look at the future...

# Goals

- #### Logging

* [x] Make scoped logger interface
* [x] Implement interface logic
* [x] Add max buffer limit before flush
* [x] Add observer like log
* [ ] Think about async write to buffer [wip]

---

- ### Config manager

* [ ] Make Interface for configuration loading

- From file
- From stream

* [ ] Add interface implementation as json/xml/tson loader

---

- ### Zip undixing utils

* [ ] Add zip undixing interface
* [ ] Make logic

---

- ### File manager

* [ ] Add interface for loading files
* [ ] Inplement interface

- As stream
- As simple file discriptor

* [ ] Make Zip utils as part of manager

---

- ### Engine core

* [ ] Make core :)
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

* [ ] Define shared module interfase
* [ ] Think about key kripted libs (loader will uncript libs and load in memory, is it real???)
* [ ] Make Logging/File manager as modules

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

* [ ] Make window class interface
* [ ] Implenment interface with SDL2

---

- ### Gui system (as module)

* [ ] Understand how imgui framework independent
* [ ] Steal some gui code)) and make widget system

- Add layout widgets
- Make font loading with sdl2 ttf lib

* [ ] Understand how process two window

---

- ### Core part 2

* [ ] Add to core opening window with views:

- Make project
- Open project

* [ ] Make project file

<details>
    <summary>Project file format</summary>
    Here will be project files format :)
</details>

---

- ### Resource manager

* [ ] Make interface for objects manager
* [ ] Make logic (use File manager with zip logic for loading data)

---

- ### Render system

* [ ] Load object with resource manager and draw it
      | It will not so simple, I know that we need some game object abstruction, but... its for test and some expiriance, idk how it realize |
* [ ] Make here points goals

---

- ### Core part 3

* [ ] Add button wich open window and use Render system for test drawing objects

---

- ### Make some object ubstruction. I think it will be different game objects manager with void\* to castom data and observer like script logic, need thinks
<details>
    <summary>Thoughts</summary>
Make template function, which will take objects from map and cast in to T type. Idk how it make better, need some ideas
</details>

---

- ### Physics system

* [ ] Chose and add Physics engine like module

---

- ### Script system

* [ ] Make single storage, which will contain map with pointer to scripts
* [ ] In develop mode it will be different dll, which load in runtime and observe some game object; In release build its one dll for language, from which we load logic
      | And this chose cool, because: we can use C++/C/Rust/Go/etc with C abi in one time!!! We even can make module which load python intrpreter and then we make script which call python script from this module. Yes, im crazy :) |

---

- ### Make build system

* [ ] System will generate all artefacts

---

- ### Some other trash :)

* [ ] IDK, ist will be in next time

---

- I think about node generated libs. If I find way how to make it, we will can change render system or something other module for engine and release artefact as a simple grapth.

- If I make something usefull, you can take it for you code

- If you have any idea, I want think with you - Evgenuy1605@yandex.ru
