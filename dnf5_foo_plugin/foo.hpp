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


#ifndef DNF5_FOO_PLUGIN_FOO_HPP
#define DNF5_FOO_PLUGIN_FOO_HPP


#include <dnf5/context.hpp>
#include <libdnf5-cli/session.hpp>

#include <string>
#include <vector>


namespace dnf5 {


class FooCommand : public Command {
public:
    explicit FooCommand(Context & context) : Command(context, "foo") {}
    void set_parent_command() override;
    void set_argument_parser() override;
    void register_subcommands() override;
    void pre_configure() override;
    void configure() override;
    void load_additional_packages() override;
    void run() override;
    void goal_resolved() override;

private:
    std::vector<std::string> positional_args{};
    std::unique_ptr<libdnf5::cli::session::BoolOption> test_switch{nullptr};
    libdnf5::OptionString * test_string_option{nullptr};
};


}  // namespace dnf5


#endif  // DNF5_COMMANDS_BUILD_DEP_BUILD_DEP_HPP
