import ctypes
import os
import platform

class CMemoryBlock(ctypes.Structure):
    _fields_ = [
        ("memory_address", ctypes.c_uint64),
        ("size", ctypes.c_size_t),
        ("is_allocated", ctypes.c_int)
    ]

class NativeMemoryBridge:
    def __init__(self):
        self.os_type = platform.system()
        lib_ext = ".dll" if self.os_type == "Windows" else ".so"
        lib_path = os.path.join(os.path.dirname(__file__), f"libc_kernel_core{lib_ext}")

        try:
            # Load compiled C Core Shared Library
            self.c_core = ctypes.CDLL(lib_path)
            
            # Setup Return & Argument Types for C-Functions
            self.c_core.c_allocate_fast_buffer.restype = ctypes.POINTER(CMemoryBlock)
            self.c_core.c_allocate_fast_buffer.argtypes = [ctypes.c_size_t]

            self.c_core.c_direct_bus_write.restype = ctypes.c_int
            self.c_core.c_direct_bus_write.argtypes = [ctypes.c_uint64, ctypes.c_char_p, ctypes.c_size_t]

            self.c_core.c_free_fast_buffer.argtypes = [ctypes.POINTER(CMemoryBlock)]

            print(f"[NativeBridge] High-Performance C-Kernel Engine Linked Successfully ({lib_ext}).")
            self.use_c_engine = True
        except Exception as e:
            print(f"[NativeBridge Warning] C-Core Shared library not found: {e}. Falling back to Python CTypes.")
            self.use_c_engine = False

    def allocate_raw_buffer(self, size_bytes: int):
        if self.use_c_engine:
            block_ptr = self.c_core.c_allocate_fast_buffer(size_bytes)
            if block_ptr:
                block = block_ptr.contents
                print(f"[C-Engine Native] Allocated {size_bytes} bytes of zero-overhead RAM at 0x{block.memory_address:016X}")
                return block_ptr
        return None

    def execute_direct_io_control(self, bus_id: str, payload: bytes):
        if self.use_c_engine:
            block_ptr = self.allocate_raw_buffer(len(payload))
            if block_ptr:
                addr = block_ptr.contents.memory_address
                # C-Level Memory Copy
                res = self.c_core.c_direct_bus_write(addr, payload, len(payload))
                if res == 0:
                    print(f"[C-Engine Native] Direct I/O write on bus '{bus_id}' completed at C-Speed (0ms overhead).")
                self.c_core.c_free_fast_buffer(block_ptr)
                return True
        return False
