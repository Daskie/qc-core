qc_setup_target(
    qc-core-cpu
    STATIC_LIBRARY
    PUBLIC_LINKS
        qc-core
    DISABLE_AVX # Can't use AVX if we're testing for AVX
)
