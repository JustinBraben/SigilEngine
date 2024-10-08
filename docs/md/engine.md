# Crash Course: engine

# Table of Contents

* [Introduction](#introduction)
* [The Engine, SceneBase, and registering Actions for a scene](#the-engine-scenebase-and-registering-events-for-a-scene)
  * [Sigil_ERROR](#sigil_error)
  * [Sigil_INIT](#sigil_init)

# Introduction

`Sigil` is a work in progress, in many
respects. These variables are some one of the few ways to customize how it
works.<br/>
In most cases, users will use Sigil for 2D game jams.

# The Engine, SceneBase, and registering Actions for a scene

The engine is used to create and configure your 2d game. The engine
constructor takes a `nlohmann::json` object for configuration.
Typical engine creation looks like:

```cpp
using json = nlohmann::json;

json config_json;
config_json["display"]["name"] = "Example Game";
config_json["display"]["width"] = 1024;
config_json["display"]["height"] = 768;

Sigil::Engine engine(config_json);

engine.init(); 
```

Scenes are used to keep track of entities, registered actions,
and systems a developer can weld to the context of a scene.
An example of adding a scene below:

```cpp
class ExampleSceneA : public Sigil::SceneBase
{
	// Code goes here to extend the scene to your choosing
};

auto exampleSceneA = std::make_shared<ExampleSceneA>();
engine.addNewScene("exampleSceneA", exampleSceneA);
```

## Sigil_ERROR

Define error variable used by `Sigil`.

## Sigil_INIT

In general, `Sigil` doesn't offer ways to change initializing the library yet.