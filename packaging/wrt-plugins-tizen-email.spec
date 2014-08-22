Name:       wrt-plugins-tizen-email
Summary:    JavaScript plugin to access email services for WebRuntime
Version:    0.1
Release:    1
Group:      Messaging/Email 
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
BuildRequires:  wrt-plugins-tizen-devel
BuildRequires:  cmake
Requires:  ss-server
Requires:  msg-service-tools

%description
JavaScript plugin to access email for WebRuntime

%package devel
Summary:    wrt-plugins-tizen-email development headers
Group:      Development/Libraries
Requires:   %{name} = %{version}

%description devel
wrt-plugins-tizen-email development headers

%prep
%setup -q -n %{name}-%{version}


%build

%define PREFIX "%{_libdir}/wrt-plugins"

export LDFLAGS+="-Wl,--rpath=%{PREFIX} -Wl,--as-needed"

cmake wrt_plugin/ -DCMAKE_INSTALL_PREFIX=%{_prefix} -DDPL_LOG="ON" -DENABLE_TIME_TRACER="OFF"

make %{?jobs:-j%jobs} VERBOSE=1

%install
mkdir -p %{buildroot}/usr/lib/systemd/system
cp vcon.sh %{buildroot}/usr/lib/systemd/system
cp email.service %{buildroot}/usr/lib/systemd/system
%make_install

%clean
rm -rf %{buildroot}

%post
wrt-installer -p
systemctl enable email

%postun

%files
%manifest wrt_plugin/wrt-plugins-tizen-email.manifest
%{_libdir}/wrt-plugins/*
%{_libdir}/systemd/system/vcon.sh
%{_libdir}/systemd/system/email.service

%files devel
%{_includedir}/*
%{_libdir}/pkgconfig/*
