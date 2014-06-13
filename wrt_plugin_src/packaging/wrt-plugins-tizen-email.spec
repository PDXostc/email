Name:       wrt-plugins-tizen-email
Summary:    JavaScript plugin to access email services for WebRuntime
Version:    0.1
Release:    1
Group:      Development/Libraries
License:    Apache-2.0
Source0:    %{name}-%{version}.tar.gz

BuildRequires:  pkgconfig(dpl-efl)
BuildRequires:  pkgconfig(wrt-plugins-commons-javascript)
BuildRequires:  pkgconfig(wrt-plugins-types)
BuildRequires:  pkgconfig(wrt-plugins-tizen-common)
BuildRequires:  pkgconfig(json-glib-1.0)
BuildRequires:  pkgconfig(uw-imap-toolkit)
BuildRequires:  pkgconfig(gthread-2.0)
BuildRequires:  pkgconfig(db-util)
BuildRequires:  pkgconfig(vconf)
BuildRequires:  pkgconfig(drm-client)
BuildRequires:  pkgconfig(contacts-service2)
BuildRequires:  pkgconfig(email-service)
BuildRequires:  boost-devel
BuildRequires:  msg-service-tools
BuildRequires:  wrt-plugins-tizen-devel
BuildRequires:  cmake

%description
JavaScript plugin to access email for WebRuntime

%package devel
Summary:    wrt-plugins-tizen-email development headers
Group:      Development/Libraries
Requires:   %{name} = %{version}

%description devel
wrt-plugins-tizen-email development headers

%prep
%setup -q

%build

%define PREFIX "%{_libdir}/wrt-plugins"

export LDFLAGS+="-Wl,--rpath=%{PREFIX} -Wl,--as-needed"

cmake . -DCMAKE_INSTALL_PREFIX=%{_prefix} -DDPL_LOG="ON" -DENABLE_TIME_TRACER="OFF"

make %{?jobs:-j%jobs} VERBOSE=1

%install
rm -rf %{buildroot}
%make_install

%post
wrt-installer -p

%postun

%files
%manifest wrt-plugins-tizen-email.manifest
%{_libdir}/wrt-plugins/*

%files devel
%{_includedir}/*
%{_libdir}/pkgconfig/*

