# dnf5-example-plugin
Examples of simple dnf5 / libdnf5 plugins

dnf5 plugins
============

These plugins are designed to add new commands to `dnf5`, e.g. in this case `dnf5 foo` command.

For debugging purposes, you can use the `DNF5_PLUGINS_DIR` environment variable to point dnf5 to the location of your `foo.so` file.

```
$ DNF5_PLUGINS_DIR=build/dnf5_foo_plugin dnf5 foo --test
```
