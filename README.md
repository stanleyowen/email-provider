# Email Service Provider

## Dependencies

The Email Service Provider uses the following libraries to compile the project:

- [Libcurl](https://curl.se/download.html)

## Compiling the project

Before compiling the project, make sure to install the libraries mentioned above. After installing the libraries, you can compile the project using the following command:

```bash
make
```

For windows users, it is recommended to have the C++ compiler with the choco package manager. To setup the choco package manager:

1. Run the command prompt (`cmd`) as an administrator.
2. Copy and paste the following command in the command prompt:
   ```bash
   @"%SystemRoot%\System32\WindowsPowerShell\v1.0\powershell.exe" -NoProfile -InputFormat None -ExecutionPolicy Bypass -Command "[System.Net.ServicePointManager]::SecurityProtocol = 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))" && SET "PATH=%PATH%;%ALLUSERSPROFILE%\chocolatey\bin"
   ```
3. After installing the choco package manager, install the `make` package using the following command:
   ```bash
   choco install make
   ```
4. Download and install the cURL library on https://curl.se/windows/
5. Extract the downloaded file and rename the folder from `curl-xxx-xxx-mingw` into `curl`.
6. Copy the folder to the `C:\` directory (make sure that the `C:/curl` directory exists).
7. Add the `C:/curl/bin`, `C:/curl/include`, and `C:/curl/lib` directories to the system environment variables.
8. To compile the project, use the following command:
   ```bash
   make
   ```
9. To run the project, use the following command:
   ```bash
   main.exe
   ```
10. To clean the project, use the following command:
    ```bash
    make clean
    ```
