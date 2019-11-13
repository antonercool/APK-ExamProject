 param ([string]$pathToCreate )

if(![System.IO.File]::Exists($pathToCreate)){
    New-Item -ItemType Directory -Force -Path $pathToCreate
}