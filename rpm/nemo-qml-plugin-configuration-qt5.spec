Name:       nemo-qml-plugin-configuration-qt5
Summary:    Configuration plugin for Nemo Mobile
Version:    0.0.0
Release:    1
Group:      System/Libraries
License:    BSD
URL:        https://github.com/nemomobile/nemo-qml-plugin-configuration
Source0:    %{name}-%{version}.tar.bz2
BuildRequires:  pkgconfig(Qt5Core)
BuildRequires:  pkgconfig(Qt5Qml)
BuildRequires:  pkgconfig(mlite5)

%description
%{summary}.

%package tests
Summary:    Configuration plugin tests
Group:      System/Libraries
Requires:   %{name} = %{version}-%{release}

%description tests
%{summary}.

%prep
%setup -q -n %{name}-%{version}

%build
%qmake5 
make %{?jobs:-j%jobs}

%install
rm -rf %{buildroot}
%qmake_install

%files
%defattr(-,root,root,-)
%dir %{_libdir}/qt5/qml/org/nemomobile/configuration
%{_libdir}/qt5/qml/org/nemomobile/configuration/libnemoconfiguration.so
%{_libdir}/qt5/qml/org/nemomobile/configuration/qmldir

%files tests
%defattr(-,root,root,-)
/opt/tests/nemo-qml-plugins/configuration

