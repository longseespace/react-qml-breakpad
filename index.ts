export type RQCrashHandlerOptions = {
  submitURL: string;
  productName?: string;
  companyName?: string;
  uploadToServer?: boolean;
  autoupload?: boolean;
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
  getAutoupload(): boolean;
  crash(): void;
  isRestartedAfterCrash(): boolean;
}

declare const RQCrashHandler: RQCrashHandlerType;

export default RQCrashHandler;
