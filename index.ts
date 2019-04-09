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

declare const RQCrashHandler: RQCrashHandlerType;

export default RQCrashHandler;