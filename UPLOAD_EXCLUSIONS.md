# Upload exclusions

This public GitHub staging copy was created from local source path:

- `D:\131_v1_1_0_for_A`

The original local folder was not initialized as a git repository. This staging copy excludes generated/local artifacts, including:

- STM32/CubeIDE build output: `Debug/`, `Release/`, `*.elf`, `*.map`, `*.list`, `*.o`, `*.d`, `*.su`
- Eclipse/CubeIDE workspace metadata: `.metadata/`
- Android build/local/signing output: `.gradle/`, `.kotlin/`, `build/`, `local.properties`, `*.jks`, `*.keystore`, `*.apk`, `*.aab`
- Agent/VCS/temp metadata: `.git/`, `.svn/`, `.hermes/`, `.omx/`, `.omc/`, `*.bak*`, `*.tmp`, `*.__tmp`, `~$*`

Android release signing credentials were removed from the staged `wws2_android/app/build.gradle.kts`. Use `wws2_android/local.properties.example` as a template for local-only values.
