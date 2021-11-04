Name:       nemo-qml-plugin-configuration-qt5
Summary:    Configuration plugin for Nemo Mobile
Version:    0.2.5
Release:    1
License:    BSD
URL:        https://github.com/sailfishos/nemo-qml-plugin-configuration/
Source0:    %{name}-%{version}.tar.bz2
BuildRequires:  pkgconfig(Qt5Core)
BuildRequires:  pkgconfig(Qt5Qml)
BuildRequires:  pkgconfig(mlite5)
BuildRequires:  sailfish-qdoc-template

%description
%{summary}.

%package tests
Summary:    Configuration plugin tests
Requires:   %{name} = %{version}-%{release}

%description tests
%{summary}.

%package doc
Summary:    Configuration plugin documentation

%description doc
%{summary}.


%prep
%setup -q -n %{name}-%{version}

%build
%qmake5 
%make_build

%install
rm -rf %{buildroot}
%qmake_install

# org.nemomobile.configuration legacy import
mkdir -p %{buildroot}%{_libdir}/qt5/qml/org/nemomobile/configuration/
ln -sf %{_libdir}/qt5/qml/Nemo/Configuration/libnemoconfiguration.so %{buildroot}%{_libdir}/qt5/qml/org/nemomobile/configuration/
sed 's/Nemo.Configuration/org.nemomobile.configuration/' < src/qmldir > %{buildroot}%{_libdir}/qt5/qml/org/nemomobile/configuration/qmldir

%files
%defattr(-,root,root,-)
%dir %{_libdir}/qt5/qml/Nemo/Configuration
%{_libdir}/qt5/qml/Nemo/Configuration/libnemoconfiguration.so
%{_libdir}/qt5/qml/Nemo/Configuration/qmldir
%{_libdir}/qt5/qml/Nemo/Configuration/plugins.qmltypes

# org.nemomobile.configuration legacy import
%dir %{_libdir}/qt5/qml/org/nemomobile/configuration
%{_libdir}/qt5/qml/org/nemomobile/configuration/libnemoconfiguration.so
%{_libdir}/qt5/qml/org/nemomobile/configuration/qmldir

%files tests
%defattr(-,root,root,-)
/opt/tests/nemo-qml-plugins/configuration

%files doc
%defattr(-,root,root,-)
%dir %{_datadir}/doc/nemo-qml-plugin-configuration
%{_datadir}/doc/nemo-qml-plugin-configuration/nemo-qml-plugin-configuration.qch
