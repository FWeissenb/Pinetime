#ifndef __HEARTRATE_SERVICE_H
#define __HEARTRATE_SERVICE_H

#include <cstdint>
#include <host/ble_gap.h>


namespace Pinetime {
  namespace Controllers {
    class HeartRateService { //UUID 0x180D
      public:
        HeartRateService();
        void Init();

        int OnValueRequested(uint16_t conn_handle, uint16_t attr_handle,
                                    struct ble_gatt_access_ctxt *ctxt);

      private:
        static constexpr uint16_t hrService {0x180D};
        static constexpr uint16_t hrMeasurement {0x2A37};
        static constexpr uint16_t bodySensorLocation {0x2A38};

        static constexpr ble_uuid16_t hrServiceUuid {
                .u { .type = BLE_UUID_TYPE_16 },
                .value = hrService
        };

        static constexpr ble_uuid16_t hrMeasurementUuid {
                .u { .type = BLE_UUID_TYPE_16 },
                .value = hrMeasurement
        };

        //TODO: check if clientCharacteristic needed --> or handled automatically by nimble?

        static constexpr ble_uuid16_t bodySensorLocationUuid {
                .u { .type = BLE_UUID_TYPE_16 },
                .value = bodySensorLocation
        };

        struct ble_gatt_chr_def characteristicDefinition[6];
        struct ble_gatt_svc_def serviceDefinition[2];


    };
  }
}
#endif