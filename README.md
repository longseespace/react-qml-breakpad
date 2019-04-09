# ReactQML Breakpad

Breakpad Integration for QML and [React QML](https://github.com/longseespace/react-qml) applications

## Installation
```sh
# install native component
qpm install com.react-qml.breakpad
# (optional) install corresponding package for react-qml application
yarn add @react-qml/breakpad
```

The package is provided as a qpm package,
[`com.react-qml.breakpad`](https://www.qpm.io/packages/com.react-qml.breakpad/index.html).  
Check their
[GitHub - Usage for App Developers](https://github.com/Cutehacks/qpm/blob/master/README.md#usage-for-app-developers)
to learn more about qpm.

## API
This package exposes a QML singleton `RQCrashHandler` with the following methods:

```typescript
export type RQCrashHandlerOptions = {
  productName?: string;
  companyName?: string;
  submitURL: string;
  uploadToServer: boolean;
  extra?: object;
};

export interface RQCrashHandlerType {
  init(options: RQCrashHandlerOptions): void;
  addExtraParameter(key: string, value: string): void;
  addExtraParameter(key: string, value: object): void;
  removeExtraParameter(key: string): void;
  getParameters(): object;
  getLastCrashReport(): string;
  hasPendingUpload(): boolean;
  sendCrashReport(crashId: string): void;
  getSubmitURL(): string;
  getProductName(): string;
  getCompanyName(): string;
  getUploadToServer(): boolean;
  crash(): void;
}
```

## Examples

Usage in ReactQML

```javascript
import CrashHandler from '@react-qml/breakpad';
CrashHandler.init({
  productName: 'Ben',
  companyName: 'Podzim',
  submitURL:
    'https://sentry.io/api/xxxxxxx/minidump/?sentry_key=xxxxx',
  extra: {
    sentry: {
      release: '0.0.1',
      environment: process.env.NODE_ENV || 'development',
      debug: process.env.NODE_ENV !== 'production',
      tags: {
        git_branch: 'develop',
      },
    },
  },
})
```

Usage in QML

```qml
import ReactQML 1.0

Item {
  Component.onCompleted: {
    RQCrashHandler.init({
      // options
    })
  }
}
```

## License
ReactQML Breakpad is available under LGPLv3.
