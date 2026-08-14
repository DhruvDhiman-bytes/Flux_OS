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

    //allocating pages on the system
    EFI_PHYSICAL_ADDRESS PhysicalAddress = 0;
    EFI_STATUS AllocatedSpace = system_table->BootServices->AllocatePages(AllocateAnyPages,EfiLoaderCode, 4, &PhysicalAddress);

    if(AllocatedSpace == EFI_SUCCESS) {
        Print(L"the amount asked memory is allocated\n");
    }
    else if (AllocatedSpace == EFI_OUT_OF_RESOURCEST) {
        Print(L"The amount of memory which was asked is not allocated\n");
    }
    else if(AllocatedSpace == EFI_NOT_FOUND) {
        Print(L"The requested page is not found\n");
    }



    // freeing up the allocated memory
    EFI_STATUS FreeSpace = system_table->BootServices->FreePages(PhysicalAddress, 4);

    if(FreeSpace == EFI_SUCCESS) {
        Print(L"The amount of memory allocated is freed up");
    }
    else if(FreeSpace == EFI_NOT_FOUND) {
        Print(L"The requested memory is not allocated with Allocatepages()\n");
    }
    else if(FreeSpace == EFI_INVALID_PARAMETER) {
        Print(L"The page is invalid");
    }
    return EFI_SUCCESS;
}
