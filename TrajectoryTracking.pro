QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DEPENDPATH  += . tools
INCLUDEPATH += . tools

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    scenecontrol.cpp \
    tools/transform.cpp \
    tools/trackingWrapper.cpp

HEADERS += \
    mainwindow.h \
    scenecontrol.h \
    tools/Transform.h \
    tools/trackingWrapper.h

FORMS += \
    mainwindow.ui \
    tools/recognition.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix:  {
INCLUDEPATH += "/usr/local/include/opencv4"

unix: LIBS += "/home/dmitry/OpenCV/buildExtra/lib/libopencv_core.so"
unix: LIBS += "/home/dmitry/OpenCV/buildExtra/lib/libopencv_tracking.so"
unix: LIBS += "/home/dmitry/OpenCV/buildExtra/lib/libopencv_videoio.so"
unix: LIBS += "/home/dmitry/OpenCV/buildExtra/lib/libopencv_video.so"
unix: LIBS += "/home/dmitry/OpenCV/buildExtra/lib/libopencv_imgcodecs.so"
}

win32:
{
INCLUDEPATH += "C:\opencv\opencv470\opencvBuildMinGW32730Extra\install\include"

win32: LIBS += "C:\opencv\opencv470\opencvBuildMinGW32730Extra\bin\libopencv_core470.dll"
win32: LIBS += "C:\opencv\opencv470\opencvBuildMinGW32730Extra\bin\libopencv_imgcodecs470.dll"
win32: LIBS += "C:\opencv\opencv470\opencvBuildMinGW32730Extra\bin\libopencv_highgui470.dll"
win32: LIBS += "C:\opencv\opencv470\opencvBuildMinGW32730Extra\bin\libopencv_tracking470.dll"
win32: LIBS += "C:\opencv\opencv470\opencvBuildMinGW32730Extra\bin\libopencv_videoio470.dll"
win32: LIBS += "C:\opencv\opencv470\opencvBuildMinGW32730Extra\bin\libopencv_video470.dll"
win32: LIBS += "C:\opencv\opencv470\opencvBuildMinGW32730Extra\bin\libopencv_imgproc470.dll"
win32: LIBS += "C:\opencv\opencv470\opencvBuildMinGW32730Extra\bin\libopencv_dnn470.dll"
}




RESOURCES += \
    Resources/Main.qrc

DISTFILES += \
    Resources/KT.png \
    Resources/KT_i.png \
    Resources/Stop.png \
    Resources/Zoom_rect.png \
    Resources/aim.png \
    Resources/aim_i.png \
    Resources/alarmClock.png \
    Resources/alarmClock_i.png \
    Resources/allMessages.png \
    Resources/allMessages_i.png \
    Resources/alpha5_d.png \
    Resources/arrowDown.png \
    Resources/arrowDown_i.png \
    Resources/arrowLeft.png \
    Resources/arrowLeft_i.png \
    Resources/arrowRight.png \
    Resources/arrowRight_i.png \
    Resources/arrowUp.png \
    Resources/arrowUpDn.png \
    Resources/arrowUpDn_i.png \
    Resources/arrowUp_i.png \
    Resources/arrows4.png \
    Resources/arrows4_i.png \
    Resources/back.png \
    Resources/back_i.png \
    Resources/bin.png \
    Resources/bin_i.png \
    Resources/binocular.png \
    Resources/binocularV.png \
    Resources/binocularV_i.png \
    Resources/binocular_i.png \
    Resources/bio.png \
    Resources/bio_i.png \
    Resources/birst.png \
    Resources/birst_i.png \
    Resources/bissMinus.png \
    Resources/bissMinus_i.png \
    Resources/bissPlus.png \
    Resources/bissPlus_i.png \
    Resources/bzd.png \
    Resources/bzda.png \
    Resources/bzdang.png \
    Resources/bzor.png \
    Resources/calculator.png \
    Resources/calculator_i.png \
    Resources/cancel.png \
    Resources/cancel_i.png \
    Resources/center.png \
    Resources/center_i.png \
    Resources/change.png \
    Resources/change_i.png \
    Resources/check.png \
    Resources/check_double.png \
    Resources/check_g.png \
    Resources/check_green.png \
    Resources/clock.png \
    Resources/clock_i.png \
    Resources/column.png \
    Resources/column_i.png \
    Resources/compare.png \
    Resources/compare_i.png \
    Resources/conditions.png \
    Resources/conditions_i.png \
    Resources/copy.png \
    Resources/copy_i.png \
    Resources/create.png \
    Resources/create_i.png \
    Resources/custom.png \
    Resources/custom_i.png \
    Resources/defence.png \
    Resources/defence_i.png \
    Resources/detail.png \
    Resources/detail_i.png \
    Resources/devision.png \
    Resources/devision_i.png \
    Resources/disclime.png \
    Resources/disclime_i.png \
    Resources/dist_0_10.png \
    Resources/dist_0_10.psd \
    Resources/dist_0_10_i.png \
    Resources/dist_0_20.png \
    Resources/dist_0_20_i.png \
    Resources/document.png \
    Resources/document_i.png \
    Resources/estimate.png \
    Resources/estimate_i.png \
    Resources/exchange.png \
    Resources/exchange_i.png \
    Resources/fflag.png \
    Resources/fflag_i.png \
    Resources/filter.png \
    Resources/filter_i.png \
    Resources/firePlan.png \
    Resources/firePlan_i.png \
    Resources/flag.png \
    Resources/flag_i.png \
    Resources/flyAvoid.png \
    Resources/flyAvoid_i.png \
    Resources/flyCorridor.png \
    Resources/flyCorridor_i.png \
    Resources/foe.png \
    Resources/foe_i.png \
    Resources/fragbio.png \
    Resources/fragpoi.png \
    Resources/fragrad.png \
    Resources/friend.png \
    Resources/friend_i.png \
    Resources/front.png \
    Resources/front_i.png \
    Resources/group.png \
    Resources/group_i.png \
    Resources/groupobj.png \
    Resources/groupobj_i.png \
    Resources/kren.png \
    Resources/kren2.PNG \
    Resources/lense.png \
    Resources/lense_i.png \
    Resources/letter.png \
    Resources/letter_i.png \
    Resources/link.png \
    Resources/link_i.png \
    Resources/litera1.png \
    Resources/litera1_i.png \
    Resources/litera2.png \
    Resources/litera2_i.png \
    Resources/litera3.png \
    Resources/litera3_i.png \
    Resources/litera4.png \
    Resources/litera4_i.png \
    Resources/log.png \
    Resources/log_i.png \
    Resources/loiting.png \
    Resources/loiting_i.png \
    Resources/map.png \
    Resources/map_i.png \
    Resources/mat.png \
    Resources/mat_i.png \
    Resources/meteo.png \
    Resources/meteo_i.png \
    Resources/minus.png \
    Resources/minus_i.png \
    Resources/monitor.png \
    Resources/monitor_i.png \
    Resources/move.png \
    Resources/move_i.png \
    Resources/moving.png \
    Resources/moving_i.png \
    Resources/msgIn.png \
    Resources/msgIn_i.png \
    Resources/msgOut.png \
    Resources/msgOut_i.png \
    Resources/navig.png \
    Resources/navig_i.png \
    Resources/newTask.png \
    Resources/newTask_i.png \
    Resources/next.png \
    Resources/next_i.png \
    Resources/nobirst.png \
    Resources/nobirst_i.png \
    Resources/nomer.png \
    Resources/nomer_i.png \
    Resources/np.png \
    Resources/np_i.png \
    Resources/objDir.png \
    Resources/objDir_i.png \
    Resources/obstan.png \
    Resources/obstan_i.png \
    Resources/off.png \
    Resources/off_i.png \
    Resources/ok.png \
    Resources/ok_i.png \
    Resources/open.png \
    Resources/open_i.png \
    Resources/orDir.png \
    Resources/orDir_i.png \
    Resources/parashut.png \
    Resources/parashut_b.png \
    Resources/parashut_i.png \
    Resources/path.png \
    Resources/pathBla.png \
    Resources/pathBla_i.png \
    Resources/pathCreate.png \
    Resources/pathCreate_i.png \
    Resources/path_i.png \
    Resources/pause.png \
    Resources/pen.png \
    Resources/pen_i.png \
    Resources/pgz.png \
    Resources/pgz2.png \
    Resources/photo.png \
    Resources/photo_i.png \
    Resources/plane.png \
    Resources/plane2.png \
    Resources/plane2_i.png \
    Resources/planeZone.png \
    Resources/planeZone_i.png \
    Resources/plane_i.png \
    Resources/plus.png \
    Resources/plus_i.png \
    Resources/poison.png \
    Resources/prepare.png \
    Resources/prepare_i.png \
    Resources/prpd.png \
    Resources/prpdPos.png \
    Resources/prpdPos_i.png \
    Resources/prpd_i.png \
    Resources/pryamaya-uglovaya-zasechka.png \
    Resources/pzas_ugol.png \
    Resources/question.png \
    Resources/question_i.png \
    Resources/radioactive.png \
    Resources/ready.png \
    Resources/ready_i.png \
    Resources/recogn.png \
    Resources/recogn_i.png \
    Resources/regCenter.png \
    Resources/regCenter_i.png \
    Resources/region.png \
    Resources/region_i.png \
    Resources/relief.png \
    Resources/relief_i.png \
    Resources/renew.png \
    Resources/renew_i.png \
    Resources/repair.png \
    Resources/repair_i.png \
    Resources/rhbz.png \
    Resources/rhbz_i.png \
    Resources/rls1.png \
    Resources/rls1_i.png \
    Resources/rls2.png \
    Resources/rls2_i.png \
    Resources/rndc.png \
    Resources/rndc_i.png \
    Resources/rop.png \
    Resources/rop_i.png \
    Resources/rotate.png \
    Resources/rotate_i.png \
    Resources/route.png \
    Resources/route_i.png \
    Resources/rubezh.png \
    Resources/rubezh_i.png \
    Resources/save.png \
    Resources/save_i.png \
    Resources/search.png \
    Resources/search2.png \
    Resources/search2_i.png \
    Resources/searchBirst.png \
    Resources/searchBirst_i.png \
    Resources/search_i.png \
    Resources/sector.png \
    Resources/sector2.png \
    Resources/sectorMinus.png \
    Resources/sectorMinus_i.png \
    Resources/sectorPlus.png \
    Resources/sectorPlus_i.png \
    Resources/sector_i.png \
    Resources/selcheck.png \
    Resources/selcheck_i.png \
    Resources/select.png \
    Resources/select_i.png \
    Resources/selfPos.png \
    Resources/selfPos_i.png \
    Resources/send.png \
    Resources/sendReady.png \
    Resources/sendReady_i.png \
    Resources/sendTime.png \
    Resources/sendTime_i.png \
    Resources/sendVnp.png \
    Resources/sendVnp_i.png \
    Resources/send_i.png \
    Resources/ship.png \
    Resources/ship_i.png \
    Resources/showTable.png \
    Resources/showTable_i.png \
    Resources/signal.png \
    Resources/signal_i.png \
    Resources/single.png \
    Resources/single_i.png \
    Resources/slopeMinus.png \
    Resources/slopeMinus_i.png \
    Resources/slopePlus.png \
    Resources/slopePlus_i.png \
    Resources/sort.png \
    Resources/sort_i.png \
    Resources/speaker.png \
    Resources/speaker_I.png \
    Resources/swap.png \
    Resources/swap_i.png \
    Resources/tangaj.png \
    Resources/tangaj2.PNG \
    Resources/tank.png \
    Resources/tank_i.png \
    Resources/targetHIt.png \
    Resources/targetHIt_i.png \
    Resources/targeting.png \
    Resources/targeting_i.png \
    Resources/task.png \
    Resources/task_i.png \
    Resources/tgp_card.png \
    Resources/tgp_card_i.png \
    Resources/topo.png \
    Resources/topoWork.png \
    Resources/topoWork_i.png \
    Resources/topo_i.png \
    Resources/track.png \
    Resources/track_i.png \
    Resources/tree.png \
    Resources/tree_i.png \
    Resources/triangularArrowLeft.png \
    Resources/triangularArrowLeft_i.png \
    Resources/triangularArrowRight.png \
    Resources/triangularArrowRight_i.png \
    Resources/uhf.png \
    Resources/uhf2.png \
    Resources/uhf2_i.png \
    Resources/uhf_i.png \
    Resources/ungroup.png \
    Resources/ungroupObj.png \
    Resources/ungroupObj_i.png \
    Resources/ungroup_i.png \
    Resources/unvisible.png \
    Resources/unvisible_i.png \
    Resources/vector.png \
    Resources/vector_i.png \
    Resources/velMinus.png \
    Resources/velMinus_i.png \
    Resources/velPlus.png \
    Resources/velPlus_i.png \
    Resources/visible.png \
    Resources/visible_i.png \
    Resources/vnp.png \
    Resources/vnp_i.png \
    Resources/vvt.png \
    Resources/vvt_i.png \
    Resources/warnind1.png \
    Resources/warnind2.png \
    Resources/warningBlack.png \
    Resources/warningBlack_i.png \
    Resources/work.png \
    Resources/work_i.png \
    Resources/wrktask.png \
    Resources/wrktask_i.png \
    Resources/zas.png \
    Resources/zas_i.png \
    Resources/zin.png \
    Resources/zin_i.png \
    Resources/zout.png \
    Resources/zout_i.png
