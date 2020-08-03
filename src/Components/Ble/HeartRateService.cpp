#include "HeartRateService.h"

using namespace Pinetime::Controllers;

constexpr ble_uuid16_t HeartRateService::hrServiceUuid;
constexpr ble_uuid16_t HeartRateService::hrMeasurementUuid;
constexpr ble_uuid16_t HeartRateService::bodySensorLocationUuid;

int HeartRateCallback(uint16_t conn_handle, uint16_t attr_handle, struct ble_gatt_access_ctxt *ctxt, void *arg) {
  auto hrService = static_cast<HeartRateService*>(arg);
  return hrService->OnValueRequested(conn_handle, attr_handle, ctxt);
}

void HeartRateService::Init() {
  int res = 0;
  res = ble_gatts_count_cfg(serviceDefinition);
  ASSERT(res == 0);

  res = ble_gatts_add_svcs(serviceDefinition);
  ASSERT(res == 0);
}


int HeartRateService::OnValueRequested(uint16_t conn_handle, uint16_t attr_handle,
                                                    struct ble_gatt_access_ctxt *ctxt) {
  const char *str;

  switch (ble_uuid_u16(ctxt->chr->uuid)) {
    case bodySensorLocation:
      str = "0"; //TODO: cant find values on bt sig page :/
      break;
    default:
      return BLE_ATT_ERR_UNLIKELY;
  }

  int res = os_mbuf_append(ctxt->om, str, strlen(str));
  return (res == 0) ? 0 : BLE_ATT_ERR_INSUFFICIENT_RES;
}

HeartRateService::HeartRateService() :
        characteristicDefinition{
                {
                        .uuid = (ble_uuid_t *) &hrMeasurementUuid,
                        .access_cb = HeartRateCallback,  //TOOD: Handle notification with nimble?
                        .arg = this,
                        .flags = BLE_GATT_CHR_F_NOTIFY,
                },
                {
                        .uuid = (ble_uuid_t *) &bodySensorLocationUuid,
                        .access_cb = HeartRateCallback,
                        .arg = this,
                        .flags = BLE_GATT_CHR_F_READ,
                },
                {
                  0
                }
        },
        serviceDefinition{
                {
                        /* Device Information Service */
                        .type = BLE_GATT_SVC_TYPE_PRIMARY,
                        .uuid = (ble_uuid_t *) &hrServiceUuid,
                        .characteristics = characteristicDefinition
                },
                {
                        0
                },
        }
         {

}
