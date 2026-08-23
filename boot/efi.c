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
    UINTN MapKey;
    VOID* Buffer = NULL;
    UINTN MemoryMapSize = 4096;
    UINTN DescriptorSize;
    UINT32 DescriptorVersion;

    /*
     * This section does the job of allocating buffer
     * that which is needed for the working of the system
     */
    EFI_STATUS AllocatedBuffer = system_table->BootServices->AllocatePool(EfiLoaderCode, 4096, &Buffer);

    if(AllocatedBuffer == EFI_SUCCESS) {
        Print(L"The amount of asked buffer is allocated\n");
    }
    else {
        Print(L"The amount of asked buffer is not allocated\n");
    }

    /*
     * This section does the job of allocating pages
     * for working of the UEFI for the system
     */
    EFI_PHYSICAL_ADDRESS PhysicalAddress = 0;
    EFI_STATUS AllocatedSpace = system_table->BootServices->AllocatePages(AllocateAnyPages,EfiBootServicesCode, 4, &PhysicalAddress);

    if(AllocatedSpace == EFI_SUCCESS) {
        Print(L"the amount asked memory is allocated\n");
    }
    else if (AllocatedSpace == EFI_OUT_OF_RESOURCES) {
        Print(L"The amount of memory which was asked is not allocated\n");
    }
    else if(AllocatedSpace == EFI_NOT_FOUND) {
        Print(L"The requested page is not found\n");
    }

    /*
     * This section of the code requires us for knowing the current memory map after allocation of the system
     * by the function used like AllocatePages() and AllocatePool() function
     */

    EFI_STATUS GetMemoryMap_allocated = system_table->BootServices->GetMemoryMap(&MemoryMapSize, (EFI_MEMORY_DESCRIPTOR*) Buffer, &MapKey, &DescriptorSize,
        &DescriptorVersion);

    /*
     * This section does the job of freeing up the allocated pages
     * by the function for the working of the system
     */
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

    /*
     * This section of the code does the job of freeing up the pool
     * allocated for the buffer side for the working of the project
     */
    EFI_STATUS FreePool = system_table->BootServices->FreePool(Buffer);

    if(FreePool == EFI_SUCCESS) {
        Print(L"The amount allocated for the buffer is freed\n");
    }
    else {
        Print(L"The amount of allocated for the buffer is not freed\n");
    }
    return EFI_SUCCESS;
}
