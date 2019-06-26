# Summary
Watching TheCherno's Game Engine series  

# How to work with this stuff
### __See sub-projects inside folder__
```
> __ workspace __
VSCode workspace, because it doesn't support nested projects
```

```
> GameEngineStudy
Game engine project

vendor/spdlog ... logging library
vendor/GLFW ..... platform layer provider 
vendor/Glad ..... OpenGL loader
vendor/imgui .... immediate-mode GUI tool
```

```
> Sandbox
Executable test project
```

### __Project setup and build__
Initial  
* Call git submodule update --init --recursive
* Call git submodule update -f

VSCode  
* See "**/.vscode/tasks.json" for build commands
* See "**/.vscode/launch.json" for run and debug commands

Premake  
* Call GenerateProjects.bat
* Use your IDE of preference

> Target output into "/bin" folder  
> Intermediate output into "/bin-int" folder  

# Current state
* WIP

# To do
* watch the videos, learn and study
