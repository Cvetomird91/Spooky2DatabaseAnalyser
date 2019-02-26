Simple GUI program that analyses a directory with Spooky2 scan output files and displays statistics about the hits. It uses LibBoost and FLTK. It is initially developed under Linux. Builds for Windows and macOS are coming up.

There's a Dockerfile to setup dev environment with the following commands:

1. Build an image with the source
``` 
docker build -t s2db:latest . 
```

2. Start a container and run a shell into it:
``` 
docker attach $(docker run -dit s2db:latest /bin/bash)
```
