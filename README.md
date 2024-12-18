# dnf5-example-plugin
Examples of simple dnf5 / libdnf5 plugins

dnf5 plugins
============

These plugins are designed to add new commands to `dnf5`, e.g. in this case `dnf5 foo` command.

For debugging purposes, you can use the `DNF5_PLUGINS_DIR` environment variable to point dnf5 to the location of your `foo.so` file.

```
$ DNF5_PLUGINS_DIR=build/dnf5_foo_plugin dnf5 foo --test
```

libdnf5 plugins
===============

These plugins do not introduce any new commands; instead, they are designed to modify the behavior of `libdnf5` itself. They are executed regardless of how `libdnf5` is used - whether through the `dnf5` command-line tool or via API calls.

For debugging you need to
1. Create a plugin configuration file (e.g., `baz.conf`) and specify its location using the `LIBDNF_PLUGINS_CONFIG_DIR` environment variable.
2. set the `pluginpath` configuration option to the location of the `baz.so` library

```
$ LIBDNF_PLUGINS_CONFIG_DIR=libdnf5_baz_plugin dnf reinstall libsolv --setopt=pluginpath=build/libdnf5_baz_plugin --assumeno
```
