cmake_minimum_required(VERSION 3.5)

project(LedgerLogic VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Charts)
find_package(Qt6 REQUIRED COMPONENTS Sql)

# Add all the project sources, including the ones from ChartOfAccount
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    FunctionsDefinition.h

    # Include the ChartOfAccount window files
    chartofaccountwindow.cpp
    chartofaccountwindow.h
    chartofaccountwindow.ui

    #Including image
    Resources.qrc


    #Including Add Account Window
    AddWindow.cpp
    AddWindow.h
    AddWindow.ui

    #Including Edit Account Window
    editwindow.cpp
    editwindow.h
    editwindow.ui

    #Including CreateInvoiceWindow
    create1.cpp
    create1.h
    create1.ui

    #Including RecordInvoicePayement Window
    readpayment.cpp
    readpayment.h
    readpayment.ui

    #Including RecordSupplier Payment
    ReadSupplierPayment.h
    ReadSupplierPayment.cpp
    ReadSupplierPayment.ui

    #Including Create Bill Window
    CreateBill.h
    CreateBill.ui
    CreateBill.cpp

    #Including Function Files
    invoicebillfunctions.cpp
    invoicebillfunctions.h

    #Including Create Journal
    CreateJournal.cpp
    CreateJournal.h
    CreateJournal.ui

    #Including Ledger Summary
    ledgersummary.cpp
    ledgersummary.h
    ledgersummary.ui
)

# Specify the path to your database file
set(DATABASE_FILE "${CMAKE_CURRENT_SOURCE_DIR}/database/AccountingDetails.db")

# Ensure the database file is copied to the build directory
file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/database")

if(EXISTS ${DATABASE_FILE})
    file(COPY ${DATABASE_FILE} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/database)

else()
    message(FATAL_ERROR "Database file does not exist: ${DATABASE_FILE}")
endif()


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(LedgerLogic
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(LedgerLogic SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(LedgerLogic
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# Link necessary libraries (Qt Widgets, Charts, and SQL)
target_link_libraries(LedgerLogic PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(LedgerLogic PRIVATE Qt6::Charts)
target_link_libraries(LedgerLogic PRIVATE Qt6::Sql)

if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.GUI)
endif()

set_target_properties(LedgerLogic PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS LedgerLogic
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(LedgerLogic)
endif()
