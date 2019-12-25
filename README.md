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

vendor/Glad ..... OpenGL loader
vendor/GLFW ..... platform layer provider
vendor/glm ...... math code library
vendor/spdlog ... logging library
vendor/imgui .... immediate-mode GUI tool
vendor/stb_image  image-processing library
```

```
> Sandbox
Executable test project
```

### __Project setup and build__
Initial  
* Call git submodule update --init --recursive
* Call git submodule update -f
* See some notes below regarding SSH keys

In case of using SSH key passphrases  
```
# on Windows you might want to modify your .gitconfig with
[credential]
	helper = manager
[url "https://github.com/"]
	insteadOf = git@github.com:

# also see
# - https://help.github.com/en/github/authenticating-to-github/working-with-ssh-key-passphrases

# hm, I didn't figure out how to use them with submodules differently
# - https://support.microsoft.com/en-us/help/4026814/windows-accessing-credential-manager
```

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
