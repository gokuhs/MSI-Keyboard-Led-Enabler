# MSI Led Enabler

Control the Steelseries keyboard LEDs on MSI laptops (GT, GE series) natively on Linux. This tool replaces the official KLM (Keyboard Led Manager) software with a lightweight, efficient daemon.

## Features
*   **Systemd Integration**: Runs as a background service automatically on boot.
*   **Persistence**: Remembers your last color configuration after rebooting.
*   **Non-Root Access**: Control your keyboard without `sudo` thanks to Udev rules.
*   **Presets**: Includes nature-inspired color presets (Rainbow, Ocean, Sunset, etc.).
*   **Efficient**: Uses blocking IPC for instant response with zero CPU usage when idle.

## Installation

### Dependencies
You need `libhidapi-dev`, `libusb-1.0-0-dev` and `libudev-dev`.
On Debian/Ubuntu/Mint:
```bash
sudo apt-get install libhidapi-dev libusb-1.0-0-dev build-essential git libudev-dev
```

### Compile and Install
```bash
git clone https://github.com/gokuhs/MSI_GT_GE_Led_Enabler
cd MSI_GT_GE_Led_Enabler
make
sudo make install
```
*This will install the binary to `/usr/bin`, set up the systemd service, and configure udev rules.*

### Uninstall
```bash
sudo make uninstall
```

## Usage

The program runs as a daemon, but you can send commands to it using the same binary from your terminal.

### Syntax
```bash
msiledenabler -mode <mode> [options] -level <0-3>
```

### Modes
1.  **Standard Modes**:
    *   `normal`: All LEDs on. Requires `-color1` (Left), `-color2` (Center), `-color3` (Right).
    *   `gaming`: Only Left area on. Requires `-color1`.
    *   `breathing`: Pulsating effect.
    *   `wave`: Wave effect.
    *   `dualcolor`: Two colors.

2.  **Presets (No colors required)**:
    *   `rainbow`: Red, Green, Blue.
    *   `hot`: Red, Orange, Yellow.
    *   `cool`: Blue, Sky, Green.
    *   `forest`: Green, Green, Orange.
    *   `ocean`: Blue, Sky, Blue.
    *   `sunset`: Orange, Red, Purple.

### Arguments
*   `-level <0-3>`: Brightness level (0=Low, 3=High).
*   `-color1, -color2, -color3`: Colors for Left, Center, and Right areas.
    *   *Valid colors*: black, red, orange, yellow, green, sky, blue, purple, white.

### Examples
```bash
# Set specific colors
msiledenabler -mode normal -color1 red -color2 green -color3 blue -level 3

# Use a preset
msiledenabler -mode ocean -level 2

# Gaming mode (Left only)
msiledenabler -mode gaming -color1 red -level 3
```

## Development
This project includes configuration for **Visual Studio Code**. Just open the folder and use the recommended workspace settings.
*   **Build**: `Ctrl+Shift+B`
*   **Debug**: `F5`

## License
**Creative Commons Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)**
You are free to use, modify, and distribute this software for non-commercial purposes. Commercial use is strictly prohibited without permission.

---

# MSI Led Enabler (Español)

Controla los LEDs del teclado Steelseries en portátiles MSI (series GT, GE) nativamente en Linux. Esta herramienta reemplaza al software oficial KLM (Keyboard Led Manager) con un demonio ligero y eficiente.

## Características
*   **Integración con Systemd**: Funciona como un servicio en segundo plano automáticamente al arrancar.
*   **Persistencia**: Recuerda tu última configuración de colores después de reiniciar.
*   **Acceso sin Root**: Controla tu teclado sin usar `sudo` gracias a las reglas Udev.
*   **Presets**: Incluye preajustes de color inspirados en la naturaleza (Arcoíris, Océano, Atardecer, etc.).
*   **Eficiente**: Utiliza IPC bloqueante para una respuesta instantánea con cero uso de CPU en reposo.

## Instalación

### Dependencias
Necesitas `libhidapi-dev`, `libusb-1.0-0-dev` y `libudev-dev`.
En Debian/Ubuntu/Mint:
```bash
sudo apt-get install libhidapi-dev libusb-1.0-0-dev build-essential git libudev-dev
```

### Compilar e Instalar
```bash
git clone https://github.com/gokuhs/MSI_GT_GE_Led_Enabler
cd MSI_GT_GE_Led_Enabler
make
sudo make install
```
*Esto instalará el binario en `/usr/bin`, configurará el servicio systemd y las reglas udev.*

### Desinstalar
```bash
sudo make uninstall
```

## Uso
Consulta la sección en inglés para ver la lista completa de comandos y ejemplos. La sintaxis es idéntica.

### Ejemplos Rápidos
```bash
# Usar el preset "Océano" con brillo medio
msiledenabler -mode ocean -level 2

# Configuración manual (Rojo - Verde - Azul)
msiledenabler -mode normal -color1 red -color2 green -color3 blue -level 3
```

## Licencia
**Creative Commons Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)**
Eres libre de usar, modificar y distribuir este software para fines no comerciales. El uso comercial está estrictamente prohibido sin permiso.
