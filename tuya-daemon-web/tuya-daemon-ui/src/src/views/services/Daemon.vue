<template>
  <div>
    <tlt-card :title="$t('Daemon Configuration')">
      <vuci-form uci-config="tuya_daemon">
        <vuci-named-section name="tuya_daemon" v-slot="{ s }">
          <vuci-form-item-switch :uci-section="s" :label="'Enabled'" name="enabled" true-value="1" false-value="0"
            :help="'Run program as Daemon'" />
          <vuci-form-item-input :uci-section="s" :label="$t('Device ID')" name="deviceid" maxlength="25" required />
          <vuci-form-item-input :uci-section="s" :label="$t('Product ID')" name="productid" maxlength="25" required />
          <vuci-form-item-input :uci-section="s" :label="$t('Device Secret')" name="devicesecret" maxlength="25"
            required />
        </vuci-named-section>
      </vuci-form>
    </tlt-card>
  </div>
</template>