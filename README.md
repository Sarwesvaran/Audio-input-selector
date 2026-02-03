# Audio-input-selector

Features (Updated)

    6-Channel Input Switching: Supports AUX, USB, Bluetooth, Optical, Wi-Fi, and HDMI ARC.

    Boot Animation: Custom frame-by-frame start-up sequence.

    List-Style Menu: Scrollable interface showing 3 items at a time with a dynamic scrollbar.

    Dual-View Mode:

        Menu Mode: For navigation and selection.

        Full-Screen Mode: Displays high-resolution (128x64) graphical screens for the active input.

    Smart Navigation: Automatically returns to the menu from the full screen when the encoder is turned.

    Memory Function: Retains the last active input after power loss.

⚙️ How It Works (Updated)

    Boot Up: Plays a custom animation, then loads the last used input from EEPROM.

    Menu Navigation:

        The screen displays a scrollable list of inputs.

        Rotate the encoder to highlight an option (indicated by a white bar).

        The currently active channel is marked with an asterisk *.

    Selection:

        Press the encoder button to confirm the selection.

        The hardware activates the corresponding LED/Relay.

        The display switches to Full-Screen Mode, showing a large graphic of the selected source.

    Return to Menu:

        While in Full-Screen mode, simply rotate the encoder to wake the display back into Menu Mode to make a new selection.