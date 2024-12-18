/*
Copyright Contributors to the libdnf project.

This file is part of libdnf: https://github.com/rpm-software-management/libdnf/

Libdnf is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 2.1 of the License, or
(at your option) any later version.

Libdnf is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with libdnf.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <libdnf5/base/transaction.hpp>
#include <libdnf5/plugin/iplugin.hpp>

#include <iostream>

using namespace libdnf5;

namespace {

constexpr const char * PLUGIN_NAME = "baz";
constexpr plugin::Version PLUGIN_VERSION{1, 0, 0};

constexpr const char * attrs[]{"author.name", "author.email", "description", nullptr};
constexpr const char * attrs_value[]{"Marek Blaha", "mblaha@redhat.com", "Baz Example Plugin."};

class Baz final : public plugin::IPlugin {
public:
    Baz(libdnf5::plugin::IPluginData & data, libdnf5::ConfigParser &) : IPlugin(data) {}
    virtual ~Baz() = default;

    PluginAPIVersion get_api_version() const noexcept override { return PLUGIN_API_VERSION; }

    const char * get_name() const noexcept override { return PLUGIN_NAME; }

    plugin::Version get_version() const noexcept override { return PLUGIN_VERSION; }

    const char * const * get_attributes() const noexcept override { return attrs; }

    const char * get_attribute(const char * attribute) const noexcept override {
        for (size_t i = 0; attrs[i]; ++i) {
            if (std::strcmp(attribute, attrs[i]) == 0) {
                return attrs_value[i];
            }
        }
        return nullptr;
    }

    void init() override {
        std::cout << "----- executing Baz::init() method -----" << std  ::endl;
    }

    void pre_base_setup() override {
        std::cout << "----- executing Baz::pre_base_setup() method -----" << std  ::endl;
    }

    void post_base_setup() override {
        std::cout << "----- executing Baz::post_base_setup() method -----" << std  ::endl;
    }

    void repos_configured() override {
        std::cout << "----- executing Baz::repos_configured() method -----" << std  ::endl;
    }

    void repos_loaded() override {
        std::cout << "----- executing Baz::repos_loaded() method -----" << std  ::endl;
    }

    void pre_add_cmdline_packages([[maybe_unused]] const std::vector<std::string> & paths) override {
        std::cout << "----- executing Baz::pre_add_cmdline_packages() method -----" << std  ::endl;
    }

    void post_add_cmdline_packages() override {
        std::cout << "----- executing Baz::post_add_cmdline_packages() method -----" << std  ::endl;
    }

    void pre_transaction([[maybe_unused]] const libdnf5::base::Transaction & transaction) override {
        std::cout << "----- executing Baz::pre_transaction() method -----" << std  ::endl;
    }

    void post_transaction([[maybe_unused]] const libdnf5::base::Transaction & transaction) override {
        std::cout << "----- executing Baz::post_transaction() method -----" << std  ::endl;
    }

    void finish() noexcept override {
        std::cout << "----- executing Baz::finish() method -----" << std  ::endl;
    }

private:
};


}  // namespace

PluginAPIVersion libdnf_plugin_get_api_version(void) {
    return PLUGIN_API_VERSION;
}

const char * libdnf_plugin_get_name(void) {
    return PLUGIN_NAME;
}

plugin::Version libdnf_plugin_get_version(void) {
    return PLUGIN_VERSION;
}

plugin::IPlugin * libdnf_plugin_new_instance(
    [[maybe_unused]] LibraryVersion library_version,
    libdnf5::plugin::IPluginData & data,
    libdnf5::ConfigParser & parser) try {
    return new Baz(data, parser);
} catch (...) {
    return nullptr;
}

void libdnf_plugin_delete_instance(plugin::IPlugin * plugin_object) {
    delete plugin_object;
}
