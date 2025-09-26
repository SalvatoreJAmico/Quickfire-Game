# Quickfire Game (Clean Version)

An interactive 2–4 player reaction game built with multiple Arduino Uno R3 boards.
Players react to a light + sound cue; the fastest reaction time is shown on an LCD.

## ✨ Features
- Multiplayer (2–4 players) and solo mode
- LCD display for results
- LEDs for feedback; disqualification for early presses
- Buzzer + white light cue
- Modular case (plexiglass/wood)

## 🧱 Hardware Design
- 1× Arduino Uno (Transmitter, T1): game logic + LCD + input buttons
- 3× Arduino Uno (Receivers, R1–R3): LEDs, buzzer, power LED

## 🔄 Communication
- T1 → R1/R2/R3 via serial commands
- R1: gameplay LEDs
- R2: white light + piezo buzzer
- R3: power LED

## 📸 Screenshots
Add images to `images/` and reference them here, e.g.:
![Poster Preview](images/poster-slide-1.png)
![System Concept](images/concept-block-diagram.png)

## 🚀 How to Build/Run
1. Assemble the circuit (LEDs, buttons, resistors, LCD, buzzer).
2. Upload sketches from `code/` to the appropriate boards.
3. Power the system (USB or battery).
4. Press Start → wait for random delay → react to the cue.
5. LCD shows winner and timing info.

## 🗺️ Notes
This repository is a cleaned personal version: it removes other students' names/UINs/emails from course artifacts
and retains only technical content for portfolio purposes.

**Author:** Salvatore Amico (samic2@uic.edu), UIC CS
