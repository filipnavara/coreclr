
build-net45:
	dotnet restore /p:CORECLR=false /p:FrameworkPathOverride=/usr/local/Cellar/mono/4.8.0.520/lib/mono/4.5
	dotnet build /p:CORECLR=false /p:FrameworkPathOverride=/usr/local/Cellar/mono/4.8.0.520/lib/mono/4.5
.PHONY: build-net45

build-coreclr:
	dotnet restore /p:CORECLR=true
	dotnet build /p:CORECLR=true
.PHONY: build-coreclr