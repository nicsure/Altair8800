#ifndef DLLMAIN_H_
#define DLLMAIN_H_
#define DLL __declspec(dllexport)

#include "pch.h"
#include "intel8080.h"

// Code by nicsure (C)2022
// https://www.youtube.com/nicsure

extern "C"
{
    typedef void(__stdcall* PortOutCallback)(UINT8, UINT8);
    typedef UINT8(__stdcall* PortInCallback)(UINT8);
    typedef void(__stdcall* StatusCallback)(UINT8*, UINT8*, BOOL);

    static PortInCallback portInCallback;
    static PortOutCallback portOutCallback;
    static StatusCallback statusCallback;

    /// <summary>
    /// Initializes the emulator but does not start it, needs to be called before Start().
    /// Init and Shutdown should both be called from the same Thread
    /// </summary>
    /// <param name="UINT8 PortInCallback(UINT8 port)"> - External method that receives Port In requests</param>
    /// <param name="void PortOutCallback(UINT8 port, UINT8 data)"> - External method that receives Port Out requests</param>
    /// <param name="UINT16 speed"> - Requested speed of the emulator in nanoseconds per TState</param>
    DLL void Init(PortInCallback, PortOutCallback, StatusCallback, UINT16);

    /// <summary>
    /// Starts the emulator after initialization. The emulator is placed into Step mode. This will block the thread until ShutDown() is called.
    /// This should be called from a different thread to Init and Shutdown.
    /// </summary>
    DLL void Start();

    /// <summary>
    /// Shuts down the emulator causing the Start() method to exit.
    /// Init and Shutdown should both be called from the same Thread
    /// </summary>
    DLL void ShutDown();

    /// <summary>
    /// Changes the speed of the emulator. A theoretical speed of 1GHz is the maximum
    /// (1 nanosecond per TState), but in reality the speed will max out at a higher value than that
    /// and will depend on the speed of the host system.
    /// </summary>
    /// <param name="UINT16 speed"> - Requested speed of the emulator in nanoseconds per TState</param>
    DLL void Speed(UINT16);

    /// <summary>
    /// Puts the emulator into Run mode
    /// </summary>
    DLL void Run();

    /// <summary>
    /// Puts the emulator into Step mode
    /// </summary>
    DLL void Stop();

    /// <summary>
    /// When in Step mode, calling this will make the emulator execute a single instruction
    /// </summary>
    DLL void Step();

    /// <summary>
    /// Performs a soft reset. All registers and flags are cleared and the program counter is set to 0x0000.
    /// If the emulator was in Run mode, it will remain in Run mode, executing from 0x0000
    /// </summary>
    DLL void Reset();

    /// <summary>
    /// Performs a hard reset. All registers, flags and RAM are cleared and the program counter is set to 0x0000.
    /// If the emulator was in Run mode, it will stop and switch to Step mode.
    /// </summary>
    DLL void HardReset();

    /// <summary>
    /// Returns a byte array pointer containing the current system state, this includes all registers, flags and memory.
    /// Although not forbidden, it is unwise to call this while in Run mode.
    /// </summary>
    /// <returns>UINT8* - 65792 length byte array</returns>
    DLL UINT8* State();

    /// <summary>
    /// Requests an Interrupt is fired
    /// </summary>
    /// <param name="UINT8 vector - The opcode of the RST instruction for the interrupt"></param>
    DLL void Interrupt(UINT8);

    /// <summary>
    /// Returns the byte in RAM at the specified address
    /// </summary>
    /// <param name="UINT16 addr"> - Address to peek</param>
    /// <returns>UINT8 - The value at the address</returns>
    DLL UINT8 Examine(UINT16);

    /// <summary>
    /// Sets the byte in RAM at the specified address to the specified value
    /// </summary>
    /// <param name="UINT16 addr"> - Address to poke</param>
    /// <param name="UINT8 data"> - Value to poke</param>
    DLL void Deposit(UINT16, UINT8);

    /// <summary>
    /// Copies data from a byte array to the emulator's RAM.
    /// This function is cumbersome to implement with C#'s P/Invoke. Instead use State() to pass back an IntPtr and use Marshal.Copy() to copy data to RAM.
    /// </summary>
    /// <param name="UINT8* data"> - Byte array to copy from</param>
    /// <param name="UINT16 addr"> - Address in RAM to copy to</param>
    /// <param name="UINT16 len"> - Length of data to copy in bytes</param>
    /// <returns></returns>
    DLL void ToRam(UINT8*, UINT16, UINT16);

    /// <summary>
    /// Turns Status reporting on or off. When off, a faster maximum speed can be achieved but you lose the blinky lights.
    /// </summary>
    /// <param name="BOOL b"> - TRUE for on, FALSE for off</param>
    /// <returns></returns>
    DLL void SetDoStatus(BOOL);

    /// <summary>
    /// Returns a BOOL indicating if the emulator is in running mode.
    /// </summary>
    /// <returns>BOOL - TRUE=Running FALSE=Not Running</returns>
    DLL BOOL IsRunning();

    /// <summary>
    /// Just used during testing of the code, unimportant.
    /// </summary>
    DLL int TestDLL();
}


#endif
