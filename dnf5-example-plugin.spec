Name:           dnf5-example-plugin
Version:        1.0.0
Release:        1%{?dist}
Summary:        Example of dnf5 plugins
License:        GPL-2.0-or-later
URL:            https://github.com/m-blaha/dnf5-example-plugin
Source0:        %{url}/archive/%{version}/dnf5-example-plugin-%{version}.tar.gz

Requires:       libdnf5%{?_isa}

BuildRequires:  cmake
BuildRequires:  gcc-c++ >= 10.1
BuildRequires:  pkgconfig(libdnf5)

# dnf5 plugin
Requires:       dnf5%{?_isa}
Requires:       libdnf5-cli%{?_isa}
BuildRequires:  pkgconfig(libdnf5-cli)
BuildRequires:  dnf5-devel

# libdnf5 plugin

%description
This is an example how to write a dnf5 or libdnf5 plugin.

%files
# dnf5 plugin
%{_libdir}/dnf5/plugins/foo_cmd_plugin.so

# libdnf5 plugin
%{_libdir}/libdnf5/plugins/baz.*
%config %{_sysconfdir}/dnf/libdnf5-plugins/baz.conf

%prep
%autosetup -p1 -n dnf5-example-plugin-%{version}

%build
%cmake
%cmake_build

%install
%cmake_install

%changelog
* Thu Dec 19 2024 Marek Blaha <mblaha@redhat.com> - 1.0.0-1
- Initial release
