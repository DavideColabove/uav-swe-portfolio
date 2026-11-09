/* ============================================================
   site-data.js — Central data source for the UAV Portfolio site.
   Edit this file to add new chapters / deepdives.
   ============================================================ */

const REPO_BASE = 'https://github.com/DavideColabove/uav-software-portfolio';
const RAW_BASE  = 'https://raw.githubusercontent.com/DavideColabove/uav-software-portfolio';
const BRANCH    = 'main';   // branch used for GitHub blob/raw links

const SITE_DATA = {
  meta: {
    title: 'UAV Software Portfolio',
    author: 'Davide Colabove',
    repo: REPO_BASE,
    description: 'Deep-dive documentation for a 3-month intensive journey mastering UAV software engineering.',
  },

  techStack: [
    'C++17/20', 'ROS 2 Humble', 'DDS', 'PX4', 'MAVSDK',
    'Gazebo', 'PyTorch', 'OpenCV', 'Docker', 'CMake'
  ],

  chapters: [
    /* ── Chapter 1 ── */
    {
      id: 'ch1',
      number: '01',
      title: 'C++ Fundamentals for Robotics',
      shortTitle: 'C++ Fundamentals',
      description: 'Memory management (Smart Pointers), concurrency (std::thread), and build systems for modern C++ in robotics.',
      status: 'completed',         // completed | in-progress | upcoming
      folder: '01_cpp_robotics',
      branch: 'main',
      summaryPdf: 'summaries/ch1_summary.pdf',
      deepdives: [
        {
          title: 'Smart Pointers & Memory Management',
          subtitle: 'RAII, Heap vs Stack, unique_ptr, shared_ptr',
          pdfPath: '01_cpp_robotics/memory_management/out/deepdive_smartptr.pdf',
          texPath: '01_cpp_robotics/memory_management/src/deepdive_smartptr.tex',
        },
        {
          title: 'Concurrency & Thread Safety',
          subtitle: 'Data Races, Mutexes, Condition Variables, Producer-Consumer',
          pdfPath: '01_cpp_robotics/concurrency/out/deepdive_concurrency.pdf',
          texPath: '01_cpp_robotics/concurrency/src/deepdive_concurrency.tex',
        },
        {
          title: 'Makefiles & Build Systems',
          subtitle: 'Manual compilation, linking, Makefile targets',
          pdfPath: '01_cpp_robotics/makefiles/out/deepdive_makefiles.pdf',
          texPath: '01_cpp_robotics/makefiles/src/deepdive_makefiles.tex',
        },
      ],
      sourceFiles: [
        { name: 'sensor_memory_node.cpp', path: '01_cpp_robotics/memory_management/src/sensor_memory_node.cpp', lang: 'C++' },
        { name: 'telemetry_mutex_node.cpp', path: '01_cpp_robotics/concurrency/src/telemetry_mutex_node.cpp', lang: 'C++' },
      ],
    },

    /* ── Chapter 2 ── */
    {
      id: 'ch2',
      number: '02',
      title: 'ROS 2 Architecture & Middleware',
      shortTitle: 'ROS 2 Architecture',
      description: 'DDS protocol, OOP patterns for nodes, workspace management with Colcon, and publisher/subscriber patterns.',
      status: 'in-progress',
      folder: '02_ros2_telemetry',
      branch: 'main',
      summaryPdf: 'summaries/ch2_summary.pdf',
      deepdives: [
        {
          title: 'The DDS Protocol',
          subtitle: 'Data Distribution Service, QoS, Discovery, Pub/Sub vs Client/Server',
          pdfPath: '02_ros2_telemetry/ros2_dds/out/deepdive_dds_protocol.pdf',
          texPath: '02_ros2_telemetry/ros2_dds/src/deepdive_dds_protocol.tex',
        },
        {
          title: 'Object-Oriented C++ for ROS 2',
          subtitle: 'Classes, Inheritance, Virtual Functions, std::bind',
          pdfPath: '02_ros2_telemetry/oop_ros2/out/deepdive_cpp_oop.pdf',
          texPath: '02_ros2_telemetry/oop_ros2/src/deepdive_cpp_oop.tex',
        },
        {
          title: 'ROS 2 Workspaces & Colcon',
          subtitle: 'Workspaces, package.xml, ament_cmake, overlays',
          pdfPath: '02_ros2_telemetry/ros2_workspace/out/deepdive_colcon_build.pdf',
          texPath: '02_ros2_telemetry/ros2_workspace/src/deepdive_colcon_build.tex',
        },
        {
          title: 'Publishers & Subscribers in C++',
          subtitle: 'rclcpp::Node, timers, message callbacks',
          pdfPath: '02_ros2_telemetry/ros2_pubsub/out/deepdive_ros2_pubsub.pdf',
          texPath: '02_ros2_telemetry/ros2_pubsub/src/deepdive_ros2_pubsub.tex',
        },
      ],
      sourceFiles: [
        { name: 'oop_telemetry_node.cpp', path: '02_ros2_telemetry/oop_ros2/src/oop_telemetry_node.cpp', lang: 'C++' },
      ],
    },

    /* ── Chapter 3 ── */
    {
      id: 'ch3',
      number: '03',
      title: 'Flight Controllers & Simulation',
      shortTitle: 'PX4 & SITL',
      description: 'PX4/ArduPilot architecture, Software-In-The-Loop simulation with Gazebo, and Ground Control Stations.',
      status: 'upcoming',
      folder: '03_px4_sitl',
      branch: 'feature/flight-controllers-sim',
      summaryPdf: 'summaries/ch3_summary.pdf',
      deepdives: [],
      sourceFiles: [],
    },

    /* ── Chapter 4 ── */
    {
      id: 'ch4',
      number: '04',
      title: 'UAV Communication (MAVLink & MAVSDK)',
      shortTitle: 'MAVLink & MAVSDK',
      description: 'MAVLink protocol internals, MAVSDK async C++ fundamentals, and offboard control algorithms.',
      status: 'upcoming',
      folder: '04_mavsdk_control',
      branch: 'feature/uav-protocols',
      summaryPdf: 'summaries/ch4_summary.pdf',
      deepdives: [],
      sourceFiles: [],
    },

    /* ── Chapter 5 ── */
    {
      id: 'ch5',
      number: '05',
      title: 'Bridge: ROS 2 meets PX4',
      shortTitle: 'ROS 2 ↔ PX4',
      description: 'MicroXRCE-DDS Agent, uORB to DDS translation layer, and sensor fusion nodes.',
      status: 'upcoming',
      folder: '05_ros2_px4_bridge',
      branch: 'feature/ros2-px4-bridge',
      summaryPdf: 'summaries/ch5_summary.pdf',
      deepdives: [],
      sourceFiles: [],
    },

    /* ── Chapter 6 ── */
    {
      id: 'ch6',
      number: '06',
      title: 'AI & Computer Vision',
      shortTitle: 'AI & Vision',
      description: 'OpenCV in C++, PyTorch/LibTorch inference, and precision landing with visual servoing.',
      status: 'upcoming',
      folder: '06_vision_landing',
      branch: 'feature/cv-ai-integration',
      summaryPdf: 'summaries/ch6_summary.pdf',
      deepdives: [],
      sourceFiles: [],
    },

    /* ── Chapter 7 ── */
    {
      id: 'ch7',
      number: '07',
      title: 'Deployment & Containerization',
      shortTitle: 'Docker Deploy',
      description: 'Linux internals for robotics, Docker fundamentals, and containerizing the complete UAV stack.',
      status: 'upcoming',
      folder: '07_deployment',
      branch: 'feature/deployment-docker',
      summaryPdf: 'summaries/ch7_summary.pdf',
      deepdives: [],
      sourceFiles: [],
    },
  ],
};

/* Helper: resolve a repo-relative path to a raw GitHub URL */
function rawUrl(relPath, branch) {
  return `${RAW_BASE}/${branch || BRANCH}/${relPath}`;
}

/* Helper: resolve to a GitHub blob URL */
function blobUrl(relPath, branch) {
  return `${REPO_BASE}/blob/${branch || BRANCH}/${relPath}`;
}

/* Helper: summary PDFs are served locally from docs/summaries/ */
function summaryUrl(chapter) {
  return chapter.summaryPdf;  // relative path like "summaries/ch1_summary.pdf"
}
