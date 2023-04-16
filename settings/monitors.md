# Monitor

## Primary Display를 설정했는데도 로그인 화면이 다른 모니터에 나타날 때

`~/.config/monitors.xml` 설정을 확인해보면
`configuration.logicalmonitor.primary` display가 분명히 설정되어 있다.

```xml
<!-- ~/.config/monitors.xml -->
<monitors version="2">
  <configuration>
    <logicalmonitor>
      <x>0</x>
      <y>0</y>
      <scale>1</scale>
      <primary>yes</primary>
      <monitor>
        <monitorspec>
          <connector>HDMI-1</connector>
          <vendor>KTC</vendor>
          <product>Q3202SQ</product>
          <serial>0x00000001</serial>
        </monitorspec>
        <mode>
          <width>2560</width>
          <height>1440</height>
          <rate>59.950550079345703</rate>
        </mode>
      </monitor>
    </logicalmonitor>
    <logicalmonitor>
      <x>2560</x>
      <y>0</y>
      <scale>1</scale>
      <monitor>
        <monitorspec>
          <connector>DP-1</connector>
          <vendor>SAM</vendor>
          <product>LC32G7xT</product>
          <serial>H4ZT400029</serial>
        </monitorspec>
        <mode>
          <width>2560</width>
          <height>1440</height>
          <rate>144.00047302246094</rate>
        </mode>
      </monitor>
    </logicalmonitor>
  </configuration>
</monitors>
```

이 설정을 `~gdm3`에 복사하고 `gdm`을 재시작하면 해결된다.

```sh
ls -d ~gdm
# /var/lib/gdm3
```

```sh
sudo cp ~/.config/monitors.xml ~gdm3/.config/monitors.xml
```

```sh
sudo systemctl restart gdm
```

[GDM](https://access.redhat.com/documentation/en-us/red_hat_enterprise_linux/7/html/desktop_migration_and_administration_guide/gdm)은
GNOME Display Manager의 약자로 GNOME 환경에서 사용하는 로그인 화면을 관리하는 프로그램이다.
그래서 GDM을 재시작하면 로그아웃이 되기 때문에 작업중이라면 저장을 먼저 해두고 진행해야 한다.
