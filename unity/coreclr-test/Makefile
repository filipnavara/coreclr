
build-net45:
	dotnet restore /p:CORECLR=false
	dotnet build /p:CORECLR=false
.PHONY: build-net45

build-coreclr:
	dotnet restore /p:CORECLR=true
	dotnet build /p:CORECLR=true
.PHONY: build-coreclr