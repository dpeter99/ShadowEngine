#define RootSig0 "RootFlags( ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT )," \
				 "CBV(b0)," \
                 "CBV(b1)," \
                 "DescriptorTable(CBV(b2, numDescriptors=1),SRV(t0, numDescriptors=1))," \
                 "StaticSampler(s0)"

#define RootSig1 "RootFlags( ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT )," \
				 "CBV(b0)," \
                 "CBV(b1)," \
                 "DescriptorTable(SRV(t0, numDescriptors=1),CBV(b2, numDescriptors=1))," \
                 "StaticSampler(s0)"
