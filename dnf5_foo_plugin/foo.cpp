/*
Copyright Contributors to the libdnf project.

This file is part of libdnf: https://github.com/rpm-software-management/libdnf/

Libdnf is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

Libdnf is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with libdnf.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "foo.hpp"

#include <libdnf5-cli/session.hpp>

#include <iostream>

namespace dnf5 {

using namespace libdnf5::cli;

void FooCommand::set_parent_command() {
    // Set a parent command and optionally also the group the command belongs to.
    std::cout << "----- executing FooCommand::set_parent_command() method -----" << std::endl;
    auto * arg_parser_parent_cmd = get_session().get_argument_parser().get_root_command();
    auto * arg_parser_this_cmd = get_argument_parser_command();
    arg_parser_parent_cmd->register_command(arg_parser_this_cmd);
}

void FooCommand::set_argument_parser() {
    // Register command arguments to the argument parser
    std::cout << "----- executing FooCommand::set_argument_parser() method -----" << std::endl;
    auto & ctx = get_context();
    auto & parser = ctx.get_argument_parser();
    auto & cmd = *get_argument_parser_command();

    // Set the description of the command (printed in the list of commands section of dnf5 --help)
    cmd.set_description("Example dnf5 plugin command foo");

    // Register positional arguments
    auto args = parser.add_new_positional_arg("args", ArgumentParser::PositionalArg::UNLIMITED, nullptr, nullptr);
    args->set_description("Positional arguments.");
    args->set_parse_hook_func(
        [this]([[maybe_unused]] ArgumentParser::PositionalArg * arg, int argc, const char * const argv[]) {
            for (int i = 0; i < argc; ++i) {
                positional_args.emplace_back(argv[i]);
            }
            return true;
        });
    cmd.register_positional_arg(args);

    // register the --test/-t switch (option without value)
    test_switch = std::make_unique<libdnf5::cli::session::BoolOption>(
          *this, "test", 't', "Test switch", false);

    // register the --test-string option with a value
    test_string_option =
        dynamic_cast<libdnf5::OptionString *>(parser.add_init_value(std::make_unique<libdnf5::OptionString>(nullptr)));
    auto test_string_arg = parser.add_new_named_arg("test_string");
    test_string_arg->set_long_name("test-string");
    test_string_arg->set_description("Test string option with a value");
    test_string_arg->set_has_value(true);
    test_string_arg->set_arg_value_help("<VALUE>");
    test_string_arg->link_value(test_string_option);
    cmd.register_named_arg(test_string_arg);

}

void FooCommand::register_subcommands() {
    // If the plugin command have any subcommands, register them
    std::cout << "----- executing FooCommand::register_subcommands() method -----" << std::endl;
}

void FooCommand::pre_configure() {
    // Adjust the configuration.
    // This method is called after parsing the command line arguments, but before loading standard configuration files.
    std::cout << "----- executing FooCommand::pre_configure() method -----" << std::endl;
}

void FooCommand::configure() {
    // Adjust the configuration.
    // This method is called after loading the configuration files, before the repository metadata are downloaded.
    // Right place to specify which repositories should be loaded (here the system repo and all enabled repos)
    std::cout << "----- executing FooCommand::configure() method -----" << std::endl;
    auto & context = get_context();
    context.set_load_system_repo(true);
    context.set_load_available_repos(Context::LoadAvailableRepos::ENABLED);
}

void FooCommand::load_additional_packages() {
    // Load additional packages that are not in the repositories
    // E.g. `repoquery` commands uses it to load also packages from rpm files
    // passed as command line arguments.
    std::cout << "----- executing FooCommand::load_additional_packages() method -----" << std::endl;
}

void FooCommand::run() {
    // Main plugin command logic goes here.
    std::cout << "----- executing FooCommand::run() method -----" << std::endl;
    // Prints values of argument passed to the command.
    std::cout << "positional arguments:" << std::endl;
    for (const auto & arg : positional_args) {
        std::cout << "    " << arg << std::endl;
    }
    std::cout << "--test switch value: " << test_switch->get_value() << std::endl;
    if (test_string_option->get_priority() == libdnf5::Option::Priority::EMPTY) {
        std::cout << "--test-string argument was not used" << std::endl;
    } else {
        std::cout << "--test-string value: " << test_string_option->get_value() << std::endl;
    }
    // If the goal does not exist, this call creates it
    auto goal = get_context().get_goal();
    // Install dnf5 (this should be no-op)
    goal->add_install("dnf5");
}

void FooCommand::goal_resolved() {
    // Called immediately after the goal is resolved, but before the
    // resulting transaction is executed.
    std::cout << "----- executing FooCommand::goal_resolved() method -----" << std::endl;
}

}  // namespace dnf5
