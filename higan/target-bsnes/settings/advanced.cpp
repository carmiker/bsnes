AdvancedSettings::AdvancedSettings(TabFrame* parent) : TabFrameItem(parent) {
  setIcon(Icon::Action::Settings);
  setText("Advanced");

  layout.setMargin(5);

  videoDriverLabel.setText("Video Driver:");
  for(auto& driver : Video::availableDrivers()) {
    ComboButtonItem item;
    item.setText(driver);
    videoDriverOption.append(item);
    if(video->driver() == driver) item.setSelected();
  }
  videoDriverOption.onChange([&] {
    auto item = videoDriverOption.selected();
    videoDriverChange.setEnabled(video->driver() != item.text());
  });
  videoDriverChange.setText("Change").setEnabled(false).onActivate([&] {
    auto item = videoDriverOption.selected();
    settings["Video/Driver"].setValue(item.text());
    if(!emulator->loaded() || item.text() == "None" || MessageDialog(
      "Warning: incompatible drivers may cause bsnes to crash.\n"
      "It is highly recommended you unload your game first to avoid data loss.\n"
      "Do you wish to proceed with the video driver change now anyway?"
    ).setParent(*settingsWindow).question() == "Yes") {
      program->saveRecoveryState();
      settings["Crashed"].setValue(true);
      settings.save();
      program->initializeVideoDriver();
      if(!video->ready()) {
        MessageDialog({
          "Error: failed to initialize ", item.text(), " video driver."
        }).setParent(*settingsWindow).error();
        settings["Video/Driver"].setValue("None");
        program->initializeVideoDriver();
        for(auto item : videoDriverOption.items()) {
          if(video->driver() == item.text()) item.setSelected();
        }
      }
      settings["Crashed"].setValue(false);
      settings.save();
      videoDriverChange.setEnabled(false);
    }
  });

  audioDriverLabel.setText("Audio Driver:");
  for(auto& driver : Audio::availableDrivers()) {
    ComboButtonItem item;
    item.setText(driver);
    audioDriverOption.append(item);
    if(audio->driver() == driver) item.setSelected();
  }
  audioDriverOption.onChange([&] {
    auto item = audioDriverOption.selected();
    audioDriverChange.setEnabled(audio->driver() != item.text());
  });
  audioDriverChange.setText("Change").setEnabled(false).onActivate([&] {
    auto item = audioDriverOption.selected();
    settings["Audio/Driver"].setValue(item.text());
    if(!emulator->loaded() || item.text() == "None" || MessageDialog(
      "Warning: incompatible drivers may cause bsnes to crash.\n"
      "It is highly recommended you unload your game first to avoid data loss.\n"
      "Do you wish to proceed with the audio driver change now anyway?"
    ).setParent(*settingsWindow).question() == "Yes") {
      program->saveRecoveryState();
      settings["Crashed"].setValue(true);
      settings.save();
      program->initializeAudioDriver();
      if(!audio->ready()) {
        MessageDialog({
          "Error: failed to initialize ", item.text(), " audio driver."
        }).setParent(*settingsWindow).error();
        settings["Audio/Driver"].setValue("None");
        program->initializeAudioDriver();
        for(auto item : audioDriverOption.items()) {
          if(audio->driver() == item.text()) item.setSelected();
        }
      }
      settings["Crashed"].setValue(false);
      settings.save();
      audioDriverChange.setEnabled(false);
    }
  });

  inputDriverLabel.setText("Input Driver:");
  for(auto& driver : Input::availableDrivers()) {
    ComboButtonItem item;
    item.setText(driver);
    inputDriverOption.append(item);
    if(input->driver() == driver) item.setSelected();
  }
  inputDriverOption.onChange([&] {
    auto item = inputDriverOption.selected();
    inputDriverChange.setEnabled(input->driver() != item.text());
  });
  inputDriverChange.setText("Change").setEnabled(false).onActivate([&] {
    auto item = inputDriverOption.selected();
    settings["Input/Driver"].setValue(item.text());
    if(!emulator->loaded() || item.text() == "None" || MessageDialog(
      "Warning: incompatible drivers may cause bsnes to crash.\n"
      "It is highly recommended you unload your game first to avoid data loss.\n"
      "Do you wish to proceed with the input driver change now anyway?"
    ).setParent(*settingsWindow).question() == "Yes") {
      program->saveRecoveryState();
      settings["Crashed"].setValue(true);
      settings.save();
      program->initializeInputDriver();
      if(!input->ready()) {
        MessageDialog({
          "Error: failed to initialize ", item.text(), " input driver."
        }).setParent(*settingsWindow).error();
        settings["Input/Driver"].setValue("None");
        program->initializeInputDriver();
        for(auto item : inputDriverOption.items()) {
          if(input->driver() == item.text()) item.setSelected();
        }
      }
      settings["Crashed"].setValue(false);
      settings.save();
      inputDriverChange.setEnabled(false);
    }
  });
}
