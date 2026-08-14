/*
 *  ========================
 *  This is the file mainly
 *  used for writing the
 *  boot loader for the operating
 *  system Flux OS.
 *  =========================
 */

#include <efi.h>
#include <efilib.h>

EFI_STATUS EFIAPI efi_main(EFI_HANDLE image, EFI_SYSTEM_TABLE *system_table) {
    InitializeLib(image, system_table);




    return EFI_SUCCESS;
}
