ANDROID APP SHORTCUT EXAMPLE
============================

이 예제는 안드로이드 7.1 (API 25) 에서 소개된 런처의 바로가기(SHORTCUT)와 관련된 API 를 어떻게 사용하는지를 보여줍니다.
이 API 는 사용자가 어플리케이션 런처 아이콘을 길게 누를 때 정의된 인텐트들을 보여줄 수 있도록 합니다.
예제에서는 정적으로 정의된 XML 을 통하거나 혹은 동적으로 런타임에서 인텐트를 등록할 수 있는 것을 보여줍니다.

당신은 안드로이드 7.1 (API 25) 의 기능으르 사용할 수 있습니다. 런처에서 당신의 앱의 특정 액션을 바로 수행할 수 있는 방법을 제공합니다.
사용자는 간단하게 런처의 아이콘을 오래 누르면 앱의 바로가지를 보여주고, 사용자가 바로가기를 누르면 관련된 앱션으로 바로 이동하게 됩니다.
이 바로가기는 사용자들을 끌어들이는 최상의 방법입니다. 그리고 사용자들이 앱을 실행하기 전에 앱의 기능을 표시할 수 있습니다.

각각의 바로가기는 하나의 인텐트와 관계되어 있습니다. 각각은 특정한 태스크나 액션을 런칭합니다. 그리고 당신은 인텐트로서 액션을 위한 바로가기를 생성할 수 있습니다.
예를 들어, 당신은 새로운 텍스트 메시지를 보내거나 예약을 하거나 게임을 만들거나 게임을 계속하거나 맵을 로딩하거나 하는 등의 바로가기를 생성할 수 있습니다.

당신은 APK 의 리소스 파일에 바로가기와 관련된 정보를 등록하여 정적으로 바로가기를 생성할 수 있으며 또한 동적으로 런타임에 바로가기를 더할 수 있습니다.
정적 바로가기는 가장 이상적이고 보편적인 액션입니다. 동적 바로가기는 사용자의 환경이나 행동, 지역 등등의 선호에 따라 강조된 액션입니다.

이 샘플은 두 가지 타입의 바로가기를 기술합니다.

당신은 당신의 앱에 다섯가지 바로가기를 제공할 수 있습니다.
앱에서 바로가기를 추가하면 바로가기를 지원하는 모든 실행기에서 바로가기를 사용할 수 있습니다. PIXEL 런처 (PIXEL 장치의 기본 런처) 혹은 NOW 런처 및
기타 바로가기를 지원하는 기타 런처등에서 사용할 수 있습니다.

바로가기를 생성하는 보다 자세한 정보는 안드로이드 개발자 가이드에서 [앱의 액션을 위한 바로가기](https://developer.android.com/guide/topics/ui/shortcuts)를 참고하시기 바랍니다.

## PREREQUISITES

- Android SDK 28
- Android Build Tools v28.0.3
- Android Support Repository
 
## SCREENSHOTS

## OVERVIEW

https://developer.android.com/guide/topics/ui/shortcuts

개발자관점에서 당신은 당신의 앱에 특정한 액션을 수행하는 바로가기를 정의할 수 있습니다.
이 바로가기는 제공된는 런처에 표시할 수 있으며 앱 사용자에게 앱에서 제공하는 기본적인 액션이나 추천하는 액션을 바로 시작할 수 있도록 도와줍니다.
이 가이드는 앱의 바로가기를 생성하고 관리하는 방법을 가르칩니다.
부가적으로 당신은 바로가기의 효과를 증진시키는 최적의 연습을 하게될 것 입니다.

### SHORTCUT TYPES

![APP SHORTCUTS ON NEXUS 6P](TODO.png)

Figure 1. 앱 바로가기 사용하기 (키액션을 보여주고 즉시 앱의 액션을 수행하기)

각각의 쇼컷은 하나 이상의 인텐트와 관계되어 있고, 사용자가 바로가기를 선택했을 때 각각의 액션을 런칭합니다.
당신의 앱에서 생성한 바로가기 타입은 앱의 사용에 의존합니다.
바로가기로 표현할 수 있는 다양한 예제는 아래와 같습니다.

- 이메일 앱에서 새로운 이메일 작성하기
- 맵 앱에서 부분적은 위치를 사용에게 보여주기
- 커뮤니케이션 앱에서 친구에게 메시지 보내기
- 미디어 앱에서 TV의 다음 에피소드를 보여주기
- 게임 앱에서 마지막 저장위치를 로딩하기

> Main Activities (Intent.ACTION_MAIN 와 Intent.CATEGORY_LAUNCHER) 만 바로가기를 가질 수 있습니다.
> 만약에 앱이 하나 이상의 main activities 를 가지고 있다면 각 activity 에 바로가기를 등록해야 합니다.

당신은 당신의 앱에 아래와 같은 타입의 바로가기를 생성할 수 있습니다.

앱번들이나 APK 를 통해서 리소스 파일에 정의된 정적 바로가기
런타임에 생성, 수정, 제거할 수 있는 동적 바로가기
만약에 사용자가 퍼미션을 보장할 경우 런타임에서 핀이 된 바로가기

> 사용자는 앱의 정적 및 동적 바로가기를 실행기에 복사하여 고정된 바로가기를 직접 만들 수도 있습니다.

바로가기를 생성하기 위해서 아래와 같은 페이지를 참고하세요.

- Create Shortcuts
- Manage Shortcuts
- Best Practices for Shortcuts
- ShortcutManager

## CREATE SHORTCUTS

당신의 앱에 특정 부분으로 빠르게 접근할 수 있도록 하여 당신의 특정 타입의 컨텐츠를 보여줄 수 있도록 하는 것이 바로가기입니다.
바로가기를 통해 컨텐츠를 어떻게 제공하는 방법은 당신의 사용 예에 의존합니다. 바로가기 컨텍스트는 앱에 의한 것일 수 있고 사용자에 의한 것일 수 있습니다.
비록 정적 바로가기 컨텍스트는 변경되지 않지만 동적 바로가기 컨텍스트는 변경이 가능합니다.
그리고 각각의 사용예에서 컨텍스트는 앱에 의하여 제공됩니다.
사용자가 앱에서 콘텐츠를 제공하는 방법을 사용자가 선택하는 경우,
고정 된 바로 가기와 같이 컨텍스트는 사용자가 정의합니다.
아래는 각각의 바로가기 타입에 따른 몇몇 시나리오를 기술합니다.

정적 바로 가기는 사용자와 앱의 상호 작용 수명 동안 일관된 구조를 사용하여 콘텐츠에 연결하는 앱에 가장 적합합니다.
대부분의 런처는 한 번에 네 개의 바로 가기 만 표시 할 수 있으므로 정적 바로 가기는 일반적인 활동에 유용합니다.
예를 들어 사용자가 일정 방식으로 전자 메일을 보려는 경우 고정 바로 가기를 사용하면 일상적인 작업 수행 경험이 일관되게됩니다.

동적 바로 가기는 상황에 맞는 앱의 작업에 사용됩니다.
예를 들어, 시작시 사용자가 현재 레벨에서 시작할 수있는 게임을 빌드하는 경우 바로 가기를 자주 업데이트해야합니다.
동적 바로 가기를 사용하면 사용자가 레벨을 지울 때마다 바로 가기를 업데이트 할 수 있습니다.

고정 된 바로 가기는 특정 사용자 중심 작업에 사용됩니다.
예를 들어, 사용자는 특정 웹 사이트를 실행기에 고정시킬 수 있습니다.
이는 사용자가 브라우저의 기본 인스턴스를 사용하는 것보다 한 단계로 웹 사이트를 탐색하는 것과 같은 사용자 지정 작업을 수행 할 수 있기 때문에 유용합니다.

### CREATE STATIC SHORTCUTS

정적 바로가기는 당신의 앱에서 일반적인 액션에 대한 링크를 제공합니다.
그리고 이 액션들은 당신의 현재 버전의 앱에서 일관성을 유지할 수 있습니다.
정적 바로가기의 좋은 예로 보낸 메시지를 확인할 수 있거나 알람을 설정할 수 있거나
날마다 수행하는 사용자의 행동을 표현할 수 있습니다.

정적 바로가기를 만들기 위해서 아래와 같은 과정을 수행하면 됩니다.

1. 안드로이드 선언 파일(AndroidManifest.xml)에서 android.intent.action.MAIN 과 android.intent.category.LAUNCHER 를 찾습니다.

2. 앱의 바로 가기가 정의 된 리소스 파일을 참조하는이 활동에 `<meta-data>` 요소를 추가하십시오.

```xml
<manifest xmlns:android="http://schemas.android.com/apk/res/android"
          package="com.example.myapplication">
  <application ... >
    <activity android:name="Main">
      <intent-filter>
        <action android:name="android.intent.action.MAIN" />
        <category android:name="android.intent.category.LAUNCHER" />
      </intent-filter>
      
      <meta-data android:name="android.app.shortcuts"
                 android:resource="@xml/shortcuts" /> 
    </activity>
  </application>
</manifest>
```

3. 새로운 리소스 파일을 생성합니다. (res/xml/shortcuts.xml)

4. 이 새로운 리소스 파일에 루트 요소로 `<shortcuts>` 를 추가히고, `<shortcut>` 리스트를 작성합니다.
   각각의 `<shortcut>` 요소에는 정적 바로가기와 관련된 정보가 담겨져 있습니다. 아이콘, 설명, 그리고 앱에서 어떻게 실행되는지에 대한 정보입니다.
   
```xml
<shortcuts xmlns:android="http://schemas.android.com/apk/res/android">
  <shortcut
    android:shortcutId="compose"
    android:enabled="true"
    android:icon="@drawable/compose_icon"
    android:shortcutShortLabel="@string/compose_shortcut_short_label1"
    android:shortcutLongLabel="@string/compose_shortcut_long_label1"
    android:shortcutDisabledMessage="@string/compose_disabled_message1">
    <intent
      android:action="android.intent.action.VIEW"
      android:targetPackage="com.example.myapplication"
      android:targetClass="com.example.myapplication.ComposeActivity" />
    <!-- If your shortcut is associated with multiple intents, include them
         here. The last intent in the list determines what the user sees when
         they launch this shortcut. -->
    <categories android:name="android.shortcut.conversation" />
  </shortcut>
  <!-- Specify more shortcuts here. -->
</shortcuts>
```

### 속성 값의 설명

다음 목록에는 정적 바로 가기 내의 다른 속성에 대한 설명이 포함되어 있습니다.
`android:shortcutId` 및 `android:shortcutShortLabel`에 값을 제공해야합니다. 다른 모든 값은 선택 사항입니다.

`android:shortcutId`

    문자열로 ShortcutManager 객체가 바로가기를 수행할 때, 바로가기를 대표하는 아이디
    속성값은 리소스 문자열로 표현할 수 없습니다.
    
`android:shortcutShortLabel`

    바로가기의 목적을 표현하는 작고 간결한 문구로 10자 이하로 제한합니다.
    보다 자세한 정보는 seeShortLabel() 을 참고하시면 됩니다.
    이 속성은 반드시 문자열 리소스로 설정애야 합니다. 예를 들어 `@string/shortcut_short_label`.
    
`android:shortcutLongLabel`

    바로가기의 목적을 설명합니다. `android:shortcutShortLabel` 과 대조적으로 25문자까지 허용합니다.
    공간이 충분하다면 런처에서는 `android:shortcutShortLabel` 대신에 `android:shortcutLongLabel`을 출력합니다.
    보다 자세한 정보는 setLongLabel() 을 참고하시기 바랍니다.
    이 속성 값은 문자열 리소스로 설정해야 합니다. 예를 들어 `@string/shortcut_long_label` 처럼 

`android:shortcutDisabledMessage`

    비활성화된 바로가기를 수행하려 할 때 앱에서 표현되는 메시지입니다.
    이 메시지는 현재 바로가기가 비활성화되어 있음을 설정하도록 합니다.
    만약에 `android:enabled` 값이 `true` 이면 아무런 효과가 없습니다.
    이 속성 값은 리소스 문자열로 설정해야 합니다. 예를 들어 `@string/shortcut_disabled_message`와 같이 표현합니다.

`android:enabled`

    지원하는 런처로부터 바로가기를 수행할지 하지 않을지를 결정합니다.
    이 속성의 기본 값은 `true`입니다.
    만약에 `false`로 설정되어 있다면 
    `android:shortcutDisabledMessage` 설정된 메시지를 통해서 왜 바로가기가 비활성화 되어 있는지 설명할 수 있습니다.
    만약에 이런 메시지를 제공하지 않는다면 가장 쉬운 방법은 XML 파일에서 바로가기 전체를 지우는 것입니다.
    
`android:icon`

    실행기가 사용자에게 바로가기를 표시할 때 사용되는 비트맵 또는 아이콘입니다.
    이 값은 이미지의 경로 또는 이미지가 포함된 리소스 파일일 수 있습니다.
    가능하면 아이콘을 사용하여 성능과 일관성을 향상 시키는 것이 좋습니다.
    
    바로 가기 아이콘에는 색조가 포함될 수 없습니다.

### 내부 요소의 설정

앱의 정적 바로 가기를 나열하는 XML 파일은 각 `<shortcut>` 요소 내에서 다음 요소를 지원합니다.
정의한 각 정적 바로 가기에 대한 intent 내부 요소를 포함해야합니다.

intent
   
    바로가기를 선택했을 때 시스템 런처의 액션
    이 intent 는 android:action 속성으로 제공합니다.
    
    인텐트 요소는 문자열 리소스여서는 안됩니다.
    
    하나의 바로가기에 여러 인텐트를 제공할 수 있습니다.
    See Manage multiple intents and activities, Set an intent, and the TaskStackBuilder class reference for details.

categories

    새 채팅 메시지 만들기와 같이 앱의 바로 가기가 수행하는 작업 유형에 대한 그룹을 제공합니다.
    
    For a list of supported shortcut categories, see the ShortcutInfo class reference.

### 동적 바로가기 생성

동적 바로가기는 컨텍스트와 밀접한 관계가 있는 특정한 링크를 제공합니다.
이 액션은 앱의 사용에 따라 달라질 수 있습니다.
그리고 앱의 실행 중에 변경이 가능합니다.
동적 바로가기는 특정 사람에게 전화를 하거나, 특정 위치로 이동하거나, 게임에서 마지막 저장위치로 로딩하거나 하는 일을 수행할 수 있습니다.
ShortcutManager API 는 아래와 같은 동적 바로가기 작업을 수행합니다.

- Publish: 동적 바로가기 전체 리스트를 재정의하거나 addDynamicShortcuts() 함수를 이용하여 바로가기 리스트에 동적으로 추가할 수 있습니다.
- Update: updateShortcuts() 를 수행합니다.
- Remove: removeDynamicShortcuts() 사용하여 동적 바로가기를 제거하거나 removeAllDynamicShortcuts() 을 이용하여 모든 동적 바로가기를 제거합니다.

For more information about performing operations on shortcuts, read Manage shortcuts and the ShortcutManager reference.

앱에서 표현되는 동적 바로가기를 생성하거나 관계된 작업은 아래와 같은 코드를 통해서 가능합니다.

> `Context.getSystemService(Class)` 를 통해서 `ShortcutManager` 클래스의 객체 인스턴스를 가지고 와야 합니다.
> ShortcutManager.class 혹은 Context.getSystemService(Context.SHORTCUT_SERVICE)

```kotlin
val shortcutManager = getSystemService<ShortcutManager>(ShortcutManager::class.java)

val shortcut = ShortcutInfo.Builder(context, "id1")
        .setShortLabel("Website")
        .setLongLabel("Open the website")
        .setIcon(Icon.createWithResource(context, R.drawable.icon_website))
        .setIntent(Intent(Intent.ACTION_VIEW,
                Uri.parse("https://www.mysite.example.com/")))
        .build()

shortcutManager!!.dynamicShortcuts = Arrays.asList(shortcut)
```

### 고정된 바로가기

안드로이드 8.0 (API level 26) 이상에서 고정된 바로가기를 생성할 수 있습니다.
정적 바로가기나 동적 바로가기와 달리 고정된 바로가기는 두 바로가기와 구분되는 바로가기를 제공합니다.
그림 1에서 두 타입의 바로가기 사이에 구분되는 바로가기를 보여줍니다.

> 사용자가가 제공되는 런처에서 핀을 수행하면 사용자는 바로가기를 고정시키는 기능을 허가하는 다이얼로그를 보여줍니다.
> 만약에 바로가기 핀을 사용하지 않도록 하면 런처는 이 요청을 취소합니다.

그림 1. 고정된 바로가기와 앱 바로가기

앱에서 고정된 바로가기를 생성하기 위해서 아래와 같은 작업을 순차적으로 수행해야 합니다.

1. `isRequestPinShortcutSupported()` 함수를 통해서 고정된 바로가기가 수행될 수 있는지 확인합니다.

2. 두가지 방법중 하나로 ShortcutInfo 객체를 생성합니니다.

- 만약에 바로가기가 이미 생성되어 있다면, ShortcutInfo 객체를 생성하고 바로가기 아이디를 삽입합니다. 시스템은 자동으로 관련된 바로가기 정보를
  객체에 설정하게 됩니다.
- 만약에 새로운 바로가기라면, 생성된 ShortcutInfo 객체에 id, intent, 라벨등을 설정합니다.
 
> 시스템은 고정된 바로가기를 자동으로 백업 및 복원하기 때문에 이 바로가기의 아이디는 안정적인 상수 문자열 또는 서버 측 식별자를 포함해야 합니다.
> 로컬에서 생성된 식별자는 다른 장치에서는 의미가 없습니다.

고정된 바로가기 생성 후에 당신의 앱을 업데이트할 수 있습니다. (updateShortcuts())

For more information, read Update shortcuts.

아래의 코드는 고정된 바로가기를 생성하는 방법을 기술 합니다.

Note: Instances of the ShortcutManager class must be obtained using Context.getSystemService(Class) with the argument ShortcutManager.class or Context.getSystemService(String) with the argument Context.SHORTCUT_SERVICE.

```kotlin
val shortcutManager = getSystemService(ShortcutManager::class.java)

if (shortcutManager!!.isRequestPinShortcutSupported) {
    // Assumes there's already a shortcut with the ID "my-shortcut".
    // The shortcut must be enabled.
    val pinShortcutInfo = ShortcutInfo.Builder(context, "my-shortcut").build()

    // Create the PendingIntent object only if your app needs to be notified
    // that the user allowed the shortcut to be pinned. Note that, if the
    // pinning operation fails, your app isn't notified. We assume here that the
    // app has implemented a method called createShortcutResultIntent() that
    // returns a broadcast intent.
    val pinnedShortcutCallbackIntent = shortcutManager.createShortcutResultIntent(pinShortcutInfo)

    // Configure the intent so that your app's broadcast receiver gets
    // the callback successfully.For details, see PendingIntent.getBroadcast().
    val successCallback = PendingIntent.getBroadcast(context, /* request code */ 0,
            pinnedShortcutCallbackIntent, /* flags */ 0)

    shortcutManager.requestPinShortcut(pinShortcutInfo,
            successCallback.intentSender)
}
```

지원되는 라이브러리를 참조하세요.
isRequestPinShortcutSupported() and requestPinShortcut(), which work on Android 7.1 (API level 25) and lower. The support library falls back to the deprecated EXTRA_SHORTCUT_INTENT extra to attempt the pinning process.

### 커스텀 바로가기 액티비티 생성하기

사용자가 바로가기를 생성하고 사용자 지정 옵션과 확인 버튼을 완성하는 데 도움이 되는 특수한 활동을 만들 수 있습니다.
그림 2는 지메일 앱에서 이러한 유형의 예를 보여줍니다.

앱 설정 파일에서, ACTION_CREATE_SHORTCUT 을 `<intent-filter>` 요소에 추가하고, 이 선언을 통해서 사용자가 바로가기를 수행할 때의 행동을
설정합니다.

- 시스템은 특정 액티비티를 시작합니다.
- 바로가기를 위한 옵션을 사용자가 설정합니다.
- 사용자는 확인 버튼을 누릅니다.
- createShortcutResultIntent() 함수를 통해서 바로가기를 생성합니다.
- 이 메서드는 인텐트를 리턴합니다. 그리고 그 인텐트는 setResult() 함수를 통해서 이전에 실행되었던 행동을 수행하도록 합니다.
- 커스터마이즈된 바로가기를 사용한 후 당신은 finish()를 호출합니다.

유사하게 당신은 설치 이후 홈 화면에서 고정된 바로가기를 시도하거나 앱이 런칭될 때 이 것을 수행할 것입니다.
이 메서드는 일반적인 워크 플로우의 하나의 부분으로 바로가기를 수행하는 것을 돕기 때문에 유용할 것 입니다.

### 바로가기 테스트

앱 바로가기 테스트를 수행하기 위해서 바로가기를 지원하는 린처를 설치하고, 아래와 같은 액션을 수행하시면 됩니다.

- 런처에서 바로가기를 보여주기 위해서 아이콘을 길게 누릅니다.
- 탭을 하거나 드래그를 하여 디바이스에 핀하세요.

## 바로가기 관리

바로 가기를 만든 후에는 앱 수명 기간 동안 바로 가기를 관리해야 할 수도 있습니다.
예를 들어, 사용자가 단축키로 특정 작업을 수행하는 빈도를 결정하여 앱을 최적화 할 수 있습니다.
다른 경우에는 고정 된 바로 가기를 비활성화하여 앱이 오래되거나 누락 된 작업을 수행하지 못하게 할 수 있습니다.
이 안내서는 바로 가기를 관리하는 몇 가지 일반적인 방법을 설명합니다.

### 바로가기 행동

다음 섹션에는 가시성, 표시 순서 및 순위를 포함한 바로가기 동작에 대한 일반적인 정보가 포함되어 있습니다.

#### 바로가기 기시성

> 중요한 보안
>
> 모든 바로가기 정보는 자격증명으로 암호화된 저장소에 저장됩니다. 그리고 사용자가 디바이스의 잠금해제를 하기 전에는 당신의 앱은 사용자의 바로가기에 접근할 수 없습니다.

정적 바로가기와 동적 바로가기는 특별한 제스쳐를 수행할 때 나타납니다.
현재 지원하는 런처에서 이 제스쳐는 앱 아이콘을 길게 누를 때 나타납니다. 그러나 이 제스쳐는 다른 앱런처에서는 다르게 행동을 할 수도 있습니다.
LauncherApps 클래스는 바로가기에 접근하기 위한 API 를 제공합니다.
런처 스스로가 고정된 바로가기를 표시하기 때문에, 항상 그들을 보여지는 상태일 것 입니다.
고정된 바로가기는 아래와 같은 상황일 때만 제거될 수 있습니다.

- 사용자가 그것을 지운다.
- 바로가기와 관련된 앱이 삭제되었다.
- 사용자가 설정에서 앱 데이터를 초기화화였다. (Settings > Apps & notifications, selecting an app, then pressing Storage > Clear storage)

### 바로가기 표시 순서

앱 바로가기를 표시할 때, 아래와 같은 순서로 보여질 것 입니다.

- 정적 바로가기: isDeclareInManifest() 함수의 값이 true 일 때
- 동적 바로가기: ShortcutInfo.isDynamic() 함수가 true 일 때

각각의 바로가기 타입에서 바로가기는 ShortcutInfo.getRank() 에 따라서 정렬될 것 입니다.
순위는 양수의 값이고, 순차적인 정수 값입니다.
updateShortcuts(List), addDynamicShortcuts(List), 혹은 setDynamicShortcuts(List) 를 통해서 순위를 업데이트할 수 있습니다.

### 다중 인텐트와 액티비티

사용자가 바로 가기를 활성화 할 때 앱이 여러 작업을 수행하도록하려면 연속적인 활동을 트리거하도록 앱을 구성 할 수 있습니다.
바로 가기 유형에 따라 여러 의도를 할당하거나 다른 활동을 시작하거나 의도 플래그를 설정하여이를 수행 할 수 있습니다.

#### 다중 인텐트 할당하기

ShortcutInfo.Builder 를 통하여 바로가기를 생성할 때, setIntents() 함수를 사용하여 다중의 인텐트를 할당할 수 있습니다.
setIntents() 를 호출하면 사용자가 바로가기를 선택할 때 앱 내에서 여러 활동을 시작하여 마지막 활동을 제외한 모든 활동을 백스택의 목록에 배치할 수 있습니다.
사용자가 기긱의 뒤로 버튼을 누르면 기기의 실행기로 돌아가지 않고 앱에서 다른 활동이 표시됩니다.

> 사용자가 바로가기를 선택한 다움 뒤로 가기 키를 누르면 앱이 리소스 파일에 나열된 바로가기의 두번째에서 마지막 인턴트에 해당하는 활동을 시작합니다.
> 이 동적 패턴은 사용자가 바로가기를 만든 백스택을 지울 때까지 뒤로 버턴을 반복해서 누르면 계속됩니다. 다음에 사용자가 뒤로 버턴을 누르면 시스템이 다시 시작 관리자로 이동합니다.

#### 하나의 액티비티에서 다른 액티비티 시작

정적 바로가기는 커스텀 인텐트 플래그를 가질 수 없습니다.
정적 바로가기의 첫번째 인텐트는 항상 Intent.FLAG_ACTIVITY_NEW_TASK 과 Intent.FLAG_ACTIVITY_CLEAR_TASK 가 설정되어 있습니다.
이것은 앱이 실행 중일 때 모든 존재하는 액티비티는 바로가기기 수행될 때 모두 종료됨을 의미합니다. 만약에 이런 것이 요구되지 않으면 trampoline 액티비티를 사용하거나
보여지지 않는 액티비티가 시작하여 Activity.onCreate(Bundle) 과 Activity.finish()를 수행하도록 해야 합니다.

- AndroidManifest.xml 파일에서 trampoline 액티비티는 android:taskAffinity="" 속성을 할당하여 포함합니다.
- 바로가기 리소스 파일에서 적정 바로가기 안에 인텐트에 trampoline 액티비티를 설정하도록 합니다.

For more information about trampoline activities, read Start one activity from another.

### 인텐트 플래그 설정

동적 바로가기는 인텐트 플래그를 설정하여 생성할 수 있습니다.
다른 플래그와 함께 Intent.FLAG_ACTIVITY_CLEAR_TASK를 지정하는 것이 좋습니다.
그렇지 않으면 앱이 실행되는 동안 다른 작업을 시작하려고하면 대상 활동이 나타나지 않을 수 있습니다.

To learn more about tasks and intent flags, read the tasks and back stack guide.

### 바로가기 업데이트 하기

각 앱런처의 아이콘은 getMaxShortcutCountPerActivity() 만큼의 바로가기를 혼합할 수 있습니다.
앱을 생성할 때 고정된 바로가기의 숫자는 한계가 없습니다.
게시자가 동적 바로가기로 제거하더라도 동적 바로가기가 고정된 경우 고정된 바로가기는 여전히 표시되고 실행이 가능합니다.
이를 통해 앱은 getMaxShortcutCountPerActivity() 보다 많은 바로가기를 가질 수 있습니다.

예를 들어, getMaxShortcutCountPerActivity() 가 4라고 하면

1. 채팅 앱은 가장 최근의 네 가지 대화 (c1, c2, c3, c4)를 나타내는 네 가지 동적 바로 가기를 게시합니다.
2. 사용자는 4개의 바로가기를 고정합니다.
3. 사용자는 c5, c6, c7 세가지 추가적인 바로가기를 생성한 후에 다시 게시합니다. 이제 리스트는 c4, c5, c6, c7이 될 것입니다.
4. 앱은 c1, c2, c3 이 제거되고 게시된 4가지 동적 바로가기 말고는 표시되지 않습니다. 그러나 c1, c2, c3 은 여전히 고정된 바로가기에 추가되며, 사용자는 그것을 실행할 수 있습니다.
   이제 사용자는 앱에서 액티비티의 링크 7개의 바로가기를 사용할 수 있습니다. 이것은 최대 바로가기 숫자와 세개의 고정된 바로가기입니다.
   앱은 updateShortcuts(List)로 사용하는 일곱개의 바로가기를 업데이트할 수 있습니다. 예를 들어,
   당신은 채팅 상태의 아이콘이 변경되었을 때 이를 업데이트할 수 있습니다.
5. addDynamicShortcuts(List) 와 setDynamicShortcuts(List) 메서드는 또한 존재하는 바로가기를 같은 아이디로 업데이트할 수 있습니다.
   그러나 두가지 방법으로 지정된 바로가기 목록을 동적 바로가기로 변환하려고 하기 때문에 동적 바로가기가 아닌 것을 업데이트하는데 사용할 수 없습니다.

보다 자세한 정보는 app shortcuts 가이드라인에서 배울 수 있으며, 바로가기를 업데이트를 포함하고 있는 문서를 읽으시면 됩니다.

### 시스템 로케일 변경 핸들

시스템 로케일 정보가 변경됨을 알려주는 Intent.ACTION_LOCALE_CHANGED 브로드캐스트 메시지를 수신하면 앱은 동적 바로가기와 고정된 바로가기를 업데이트할 수 있습니다.

### 바로가기 사용 추적하기

정적 그리고 동적 바로가기가 표시되는 동안의 상태를 결정하기 위해서 런처는 바로가기의 활성 히스토리를 조사할 수 있습니다.
다음 이벤트 중 하나가 발생할 때 reportShortcutUsed () 메서드를 호출하고 바로 가기 ID를 전달하여 사용자가 앱 내에서 특정 작업을 완료하는시기를 추적 할 수 있습니다.

    사용자가 주어진 아이디의 바로가기를 선택하였을 때
    앱 내에서 사용자는 동일한 바로 가기에 해당하는 작업을 수동으로 완료합니다.

    The user selects the shortcut with given id.
    Within the app, the user manually completes the action corresponding to the same shortcut.

### 바로가기 비활성화

앱과 사용자가 바로가기를 기기의 런처에 고정할 수 있기 때문에 고정된 바로가기는 사용자에게 앱에서 데이터가 없거나 더 이상 존재하지 않는 작업을 지시할 수 있습니다.
이 상황을 관리하려면 disableShortcuts() 를 호출하여 사용자가 선택하지 못하게 하도록 바로가기를 비활성화할 수 있습니다.
disableShortcuts() 은 정적 및 동적 바로가기 목록에서 지정된 바로가기를 제거하고 이러한 바로가기의 고정된 사본을 비활성화 합니다.

당신은 이 함수를 상속하여 커스텀 에러 메시지를 출력할 수 있습니다.
어떤 비활성화 바로가기를 수행하려 할 때 이 에러 메시지가 출력되도록 할 수 있습니다.

> 만약에 정적 바로가기가 삭제되었을 때 시스템은 이 바로가기를 비활성화합니다.

### RATE LIMITING

setDynamicShortcuts(), addDynamicShortcuts() 또는 updateShortcuts() 메소드를 사용하는 경우 백그라운드 앱, 현재 활동 또는 서비스가 없는 앱에서 특정 횟수만큼 이러한 메서드를 호출할 수 있다는 점을 유의하셔야 합니다.
Rating Limit 가 활성회되어 있다면 isRateLimitingActive() 는 true 를 리턴합니다.
그러나 특정 이벤트 중에 속도 제한이 재설정되므로 백그라운드 앱에서도 속도 제한에 다시 도달 할 때까지 ShortcutManager 메서드를 호출 할 수 있습니다.
이 이벤트는 아래와 같습니다.

앱의 포그라운드가 되었을 때
시스템 로케일이 변경되었을 때
사용자가 인라인 응답 액션을 수행할 때

개발 또는 테스트 중에 속도 제한이 발생하는 경우 장치 설정에서 개발자 옵션> ShortcutManager 속도 제한 재설정을 선택하거나 adb에 다음 명령을 입력 할 수 있습니다.

```shell script
$ adb shell cmd shortcut reset-throttling [ --user your-user-id ]
```

### 백업 및 복원

앱의 매니페스트 파일에 android:allowBackup="true" 속성을 할당하여 사용자가 기기를 변경할 때 앱에서 백업 및 복원 작업을 수행하도록 할 수 있습니다.
백업 및 복원을 허용하는 경우 앱 바로가기에 대한 다음 사항에 유의하여야 합니다.

    1. 정적 바로가기는 자동으로 계시되면, 사용자가 새 장치에 앱을 다시 설치한 후에만 가능합니다.
    2. 동적 바로 가기는 백업되지 않으므로 사용자가 새 장치에서 앱을 열 때이를 다시 게시하려면 앱에 논리를 포함시켜야합니다.
    3. 고정 된 단축키는 장치의 런처에 자동으로 복원되지만 시스템은 고정 된 단축키와 관련된 아이콘을 백업하지 않습니다.
    
다음 코드 스 니펫은 앱의 동적 바로 가기를 복원하는 가장 좋은 방법과 앱의 고정 된 바로 가기가 유지되는지 확인하는 방법을 보여줍니다.

```kotlin
class MyMainActivity : Activity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        val shortcutManager = getSystemService(ShortcutManager::class.java)

        if (shortcutManager!!.dynamicShortcuts.size == 0) {
            // Application restored. Need to re-publish dynamic shortcuts.
            if (shortcutManager.pinnedShortcuts.size > 0) {
                // Pinned shortcuts have been restored. Use
                // updateShortcuts() to make sure they contain
                // up-to-date information.
            }

        }
    }
    // ...
}
```

추가적인 자원

Android AppShortcuts 샘플은이 페이지에서 다루는 워크 플로우 사용을 추가로 보여줍니다.

## 바로가기 샘플

앱 바로가기를 생성하거나 디자인할 때 이 가이드라인을 참고하시면 됩니다.

### 디자인 가이드라인

앱 바로가기를 만들 때 시스템앱에서 사용하는 바로가기의 비쥬얼 일관성을 의해서 앱 바로가기 디자인 가이드라인을 참고하세요.

### 4개의 구별되는 바로가기를 생성할 것

현재 API 는 5가지의 정적 및 동적 바로가기를 지원하지만 런처에서 시각적인 모양을 위하여 우리는 구별되는 4가지의 바로가기를 게시하기를 추천합니다.

### 바로가기 설명 길이

런처에서 앱 바로가기 메뉴의 공간은 제한적입니다.
짧은 설명은 10자이며, 긴 설명은 25자 이하입니다.

### 바로가기와 액션 사용 히스토리를 유지하세요.

생성하는 각 바로 가기에 대해 사용자가 앱 내에서 동일한 작업을 직접 수행 할 수있는 다양한 방법을 고려하십시오.
이러한 각 상황에서 런처가 사용자가 바로 가기를 나타내는 작업을 얼마나 자주 수행하는지에 대한 정확한 기록을 유지하도록 reportShortcutUsed ()를 호출해야합니다.

### 의미가 유지 될 때만 바로 가기 업데이트

동적이고 고정 된 단축키를 변경할 때는 그 의미를 유지 한 단축키 정보를 변경할 때만 updateShortcuts ()를 호출하십시오.
그렇지 않으면 다시 만드는 바로 가기 유형에 따라 다음 방법 중 하나를 사용해야합니다.

    1. Dynamic shortcuts: addDynamicShortcuts() or setDynamicShortcuts().
    2. Pinned shortcuts: requestPinShortcut().

예를 들어, 슈퍼마켓으로 이동하기위한 바로 가기를 만든 경우 슈퍼마켓의 이름은 변경되었지만 위치는 동일하게 유지되면 바로 가기를 업데이트하는 것이 좋습니다. 그러나 사용자가 다른 슈퍼마켓에서 쇼핑을 시작했다면 새로운 바로 가기를 만드는 것이 좋습니다.

#### 앱을 시작할 때마다 동적 바로 가기 확인

사용자가 새 장치로 데이터를 복원하면 동적 바로 가기가 유지되지 않습니다. 따라서 백업 및 복원의 코드 스 니펫에 표시된 것처럼 앱을 시작할 때마다 getDynamicShortcuts ()에서 반환 한 객체 수를 확인하고 필요에 따라 동적 바로 가기를 다시 게시하는 것이 좋습니다.
