system_ss.add(when: 'CONFIG_PXB',
               if_true: files(
                   'cxl-component-utils.c',
               ))
system_ss.add(when: 'CONFIG_CXL',
               if_true: files(
                   'cxl-device-utils.c',
                   'cxl-mailbox-utils.c',
                   'cxl-host.c',
                   'cxl-cdat.c',
                   'cxl-events.c',
                   'switch-mailbox-cci.c',
               ))
stub_ss.add(files(
                   'cxl-host-stubs.c',
               ))
