You can find instructions on how to access computing resources at CIMS at this
[link](https://cims.nyu.edu/webapps/content/systems/resources/computeservers).
On the CIMS machines, you will need to load the module gcc-8.1 using
the command: module load gcc-8.1

## Notes on module command

On CIMS machines (and on most other HPC environments), there are many different
versions of compilers, libraries and other software installed. The module
utility allows you the manage which particular version of a software is
accessible (to avoid conflicts from multiple different versions).

```bash
  module avail # list available modules
  module purge # unload all modules
  module load <package-name> # load a module
  module unload <package-name> # unload a module
  module list # list currently loaded modules
```

